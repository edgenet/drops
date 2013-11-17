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
//  Constructor, creates a new drops agent.

drops_t *
drops_new (const char *directory)
{
    drops_t *self = (drops_t *) zmalloc (sizeof (drops_t));
    assert (self);

    //  Start drops agent and wait for it to be ready
    self->ctx = zctx_new ();
    self->pipe = zthread_fork (self->ctx, drops_agent_main, NULL);
    if (self->pipe) {
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
//  Destructor, destroys the agent. At present this is the only way to
//  stop the drops agent.

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


//  --------------------------------------------------------------------------
//  Self test of this class

void
drops_test (bool verbose)
{
    printf (" * drops: ");

    //  @selftest
    //  Create temporary directory for test files
#   define TESTDIR ".test_drops"
    zsys_dir_create (TESTDIR);

    //  Create and destroy an drops instance
    drops_t *drops = drops_new (TESTDIR);
    drops_destroy (&drops);

    //  Delete all test files
    zdir_t *dir = zdir_new (TESTDIR, NULL);
    zdir_remove (dir, true);
    zdir_destroy (&dir);
    //  @end
    printf ("OK\n");
}
