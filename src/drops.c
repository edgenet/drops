/*  =========================================================================
    drops - start/stop drops file sharing service

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================
*/

/*
@header
    To be written.
@discuss
@end
*/

#include "drops_classes.h"

//  ---------------------------------------------------------------------
//  Structure of our class

struct _drops_t {
    void *pipe;                 //  Pipe through to agent
    zctx_t *ctx;                //  Our global ZMQ context
};


//  ---------------------------------------------------------------------
//  Constructor, creates a new drops agent

drops_t *
drops_new (const char *path)
{
    drops_t *self = (drops_t *) zmalloc (sizeof (drops_t));
    assert (self);

    //  Start drops agent and wait for it to be ready
    self->ctx = zctx_new ();
    self->pipe = zthread_fork (self->ctx, drops_agent_main, NULL);
    if (self->pipe) {
        //  Pass path to drops agent as startup argument
        zstr_send (self->pipe, path);
        //  Wait for handshake from agent telling us it's ready
        char *status = zstr_recv (self->pipe);
        if (strneq (status, "OK"))
            drops_destroy (&self);
        zstr_free (&status);
    }
    else
        drops_destroy (&self);
    return self;
}


//  ---------------------------------------------------------------------
//  Destructor, ends and destroys a drops service

void
drops_destroy (drops_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        drops_t *self = *self_p;
        if (self->pipe) {
            zstr_send (self->pipe, "TERMINATE");
            char *reply = zstr_recv (self->pipe);
            zstr_free (&reply);
        }
        zctx_destroy (&self->ctx);
        free (self);
        *self_p = NULL;
    }
}


//  ---------------------------------------------------------------------
//  Receive next message from drops instance

zmsg_t *
drops_recv (drops_t *self)
{
    assert (self);
    zmsg_t *msg = zmsg_recv (self->pipe);
    return msg;
}


//  ---------------------------------------------------------------------
//  Return handle to the drops instance, for polling

void *
drops_socket (drops_t *self)
{
    assert (self);
    return self->pipe;
}


//  --------------------------------------------------------------------------
//  Self test of this class

void
drops_test (bool verbose)
{
    printf (" * drops: ");

    //  @selftest
    //  Create temporary directory for test files
#   define TESTDIR ".test_drops"
    
    //  Create two drops instances and test some to and fro
    zsys_dir_create (TESTDIR "/box1");
    drops_t *drops1 = drops_new (TESTDIR "/box1");
    zsys_dir_create (TESTDIR "/box2");
    drops_t *drops2 = drops_new (TESTDIR "/box2");

    zclock_sleep (100);

    zfile_t *file = zfile_new (TESTDIR "/box1", "bilbo");
    int rc = zfile_output (file);
    assert (rc == 0);
    zchunk_t *chunk = zchunk_new (NULL, 100);
    zchunk_fill (chunk, 0, 100);
    rc = zfile_write (file, chunk, 1000000);
    assert (rc == 0);
    zchunk_destroy (&chunk);
    zfile_close (file);


    drops_destroy (&drops2);
    drops_destroy (&drops1);

    //  Delete all test files
//     zdir_t *dir = zdir_new (TESTDIR, NULL);
//     zdir_remove (dir, true);
//     zdir_destroy (&dir);
    //  @end
    zclock_sleep (100);
    printf ("OK\n");
}
