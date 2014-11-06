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

#include "../include/drops.h"
#include "drops_classes.h"

//  ---------------------------------------------------------------------
//  Structure of our class

struct _drops_t {
    void *pipe;                 //  Pipe through to agent
    zctx_t *ctx;                //  Our global ZMQ context
};


//  ---------------------------------------------------------------------
//  Constructor, creates a new drops agent
//  Note: this should be rebuilt using CZMQ zactors

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

    //  Give time for nodes to discover each other and interconnect
    zclock_sleep (100);

    FILE *output = fopen (TESTDIR "/box1/bilbo", "w");
    fprintf (output, "Hello, world");
    fclose (output);

    //  Directory monitoring is once per second at present, so this gives
    //  time for box1 to see its new file, and send it to box2
    zclock_sleep (1200);

    char buffer [256];
    FILE *input = fopen (TESTDIR "/box2/bilbo", "r");
    assert (input);
    char *result = fgets (buffer, 256, input);
    assert (result == buffer);
    assert (streq (buffer, "Hello, world"));
    fclose (input);

    drops_destroy (&drops2);
    drops_destroy (&drops1);

    //  Delete all test files
    zdir_t *dir = zdir_new (TESTDIR, NULL);
    zdir_remove (dir, true);
    zdir_destroy (&dir);

    //  @end
    zclock_sleep (100);
    printf ("OK\n");
}
