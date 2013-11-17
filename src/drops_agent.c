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
    bool terminated;            //  API shut us down
    zyre_t *zyre;               //  Zyre node instance
} s_agent_t;

static s_agent_t *s_agent_new (zctx_t *ctx, void *pipe);
static void s_agent_destroy (s_agent_t **self_p);
static int s_recv_from_api (s_agent_t *self);


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
    zpoller_t *poller = zpoller_new (self->pipe, NULL);

    while (!zpoller_terminated (poller)) {
        void *which = zpoller_wait (poller, -1);
        if (which == self->pipe)
            s_recv_from_api (self);

        if (self->terminated)
            break;
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
    char *status = zstr_recv (pipe);
    assert (streq (status, "OK"));
    zstr_free (&status);

    zstr_send (pipe, "TERMINATE");
    char *reply = zstr_recv (pipe);
    zstr_free (&reply);
    zctx_destroy (&ctx);

    printf ("OK\n");
}
