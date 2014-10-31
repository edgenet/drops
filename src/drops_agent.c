/*  =========================================================================
    drops_agent - work with background drops agent

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================
*/

#include "drops_classes.h"

//  -------------------------------------------------------------------------
//  Structure of our class, used in this source only

typedef struct {
    zctx_t *ctx;                //  CZMQ context
    void *pipe;                 //  Pipe back to application
    char *path;                 //  Path we are monitoring
    bool terminated;            //  API shut us down
    zyre_t *zyre;               //  Zyre node instance
    zdir_t *dir;                //  Monitored directory
} s_agent_t;

static s_agent_t *s_agent_new (zctx_t *ctx, void *pipe);
static void s_agent_destroy (s_agent_t **self_p);
static int s_recv_from_api (s_agent_t *self);
static int s_recv_from_zyre (s_agent_t *self);
static void s_check_directory (s_agent_t *self);


//  -------------------------------------------------------------------------
//  This is the agent thread. It starts up by creating an agent structure,
//  then polls the API pipe and other sockets for activity until it gets a
//  TERMINATE command from the API, at which point it exits.

void
drops_agent_main (void *args, zctx_t *ctx, void *pipe)
{
    //  Create agent instance to pass around
    s_agent_t *self = s_agent_new (ctx, pipe);
    if (!self)                  //  Interrupted
        return;
    zstr_send (self->pipe, "OK");

    //  These are the sockets we will monitor for activity
    zpoller_t *poller = zpoller_new (
        self->pipe, zyre_socket (self->zyre), NULL);

    while (!zpoller_terminated (poller)) {
        //  Check directory once a second; this is a pretty nasty way of
        //  doing it, but portable and simple. Later I'd like to use file
        //  system monitoring library and get events back over a socket.
        void *which = zpoller_wait (poller, 1000);
        if (which == self->pipe)
            s_recv_from_api (self);
        else
        if (which == zyre_socket (self->zyre))
            s_recv_from_zyre (self);
        
        if (self->terminated)
            break;
        
        s_check_directory (self);
    }
    zpoller_destroy (&poller);
    s_agent_destroy (&self);
}


//  -------------------------------------------------------------------------
//  Constructor

static s_agent_t *
s_agent_new (zctx_t *ctx, void *pipe)
{
    s_agent_t *self = (s_agent_t *) zmalloc (sizeof (s_agent_t));
    self->ctx = ctx;
    self->pipe = pipe;
    self->path = zstr_recv (self->pipe);
    self->dir = zdir_new (self->path, NULL);
    self->zyre = zyre_new (NULL);
    zyre_start (self->zyre);
    zyre_join (self->zyre, "DROPS");
    return self;
}


//  -------------------------------------------------------------------------
//  Destructor

static void
s_agent_destroy (s_agent_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        s_agent_t *self = *self_p;
        zdir_destroy (&self->dir);
        zyre_destroy (&self->zyre);
        free (self->path);
        free (self);
        *self_p = NULL;
    }
}


//  -------------------------------------------------------------------------
//  Here we handle the different control messages from the front-end

static int
s_recv_from_api (s_agent_t *self)
{
    //  Get the whole message off the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    char *command = zmsg_popstr (request);
    if (!command)
        return -1;                  //  Interrupted

    if (streq (command, "TERMINATE")) {
        self->terminated = true;
        zstr_send (self->pipe, "OK");
    }
    free (command);
    zmsg_destroy (&request);
    return 0;
}


//  -------------------------------------------------------------------------
//  Here we handle events coming from the Zyre node

static int
s_recv_from_zyre (s_agent_t *self)
{
    zyre_event_t *event = zyre_event_new (self->zyre);
    if (zyre_event_type (event) == ZYRE_EVENT_SHOUT
    && streq (zyre_event_group (event), "DROPS")) {
        zmsg_t *msg = zyre_event_msg (event);
        char *operation = zmsg_popstr (msg);
        
        if (streq (operation, "CREATE")) {
            char *filename = zmsg_popstr (msg);
            zframe_t *frame = zmsg_pop (msg);
            zfile_t *file = zfile_new (self->path, filename);
            zfile_output (file);
            fwrite (zframe_data (frame), 1, zframe_size (frame), zfile_handle (file));
            zfile_destroy (&file);
            zframe_destroy (&frame);
            zstr_send (self->pipe, filename);
            free (filename);
        }
        free (operation);
    }
    zyre_event_destroy (&event);
    return 0;
}


//  -------------------------------------------------------------------------
//  Check for any changes to directory

static void
s_check_directory (s_agent_t *self)
{
    //  Get latest snapshot and build a patches list for any changes
    //  All patches are built using a virtual path starting at "/"
    zdir_t *dir = zdir_new (self->path, NULL);
    zlist_t *patches = zdir_diff (self->dir, dir, "/");

    //  Drop old directory and replace with latest version
    zdir_destroy (&self->dir);
    self->dir = dir;

    while (zlist_size (patches)) {
        zdir_patch_t *patch = (zdir_patch_t *) zlist_pop (patches);
        if (zdir_patch_op (patch) == patch_create) {
            //  Shout new files to DROPS group
            //  Stupidest possible approach: send whole file as one frame
            //  Truncate file at arbitrary limit of 10MB
            zfile_t *file = zdir_patch_file (patch);
            if (zfile_input (file) == 0) {
                zchunk_t *chunk = zfile_read (file, 10 * 1024 * 1024, 0);
                assert (chunk);
                zmsg_t *msg = zmsg_new ();
                zmsg_addstr (msg, "CREATE");
                zmsg_addstr (msg, zdir_patch_vpath (patch));
                zmsg_add (msg, zframe_new (zchunk_data (chunk), zchunk_size (chunk)));
                zchunk_destroy (&chunk);
                zyre_shout (self->zyre, "DROPS", &msg);
            }
        }
        zdir_patch_destroy (&patch);
    }
    zlist_destroy (&patches);
}


//  --------------------------------------------------------------------------
//  Self test of this class

void
drops_agent_test (bool verbose)
{
    printf (" * drops_agent: ");

    zctx_t *ctx = zctx_new ();
    assert (ctx);

    void *pipe = zthread_fork (ctx, drops_agent_main, NULL);
    assert (pipe);
    zstr_send (pipe, ".");
    char *status = zstr_recv (pipe);
    assert (streq (status, "OK"));
    zstr_free (&status);

    zstr_send (pipe, "TERMINATE");
    char *reply = zstr_recv (pipe);
    zstr_free (&reply);
    zctx_destroy (&ctx);

    printf ("OK\n");
}
