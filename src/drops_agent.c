/*  =========================================================================
    drops_agent - work with background drops agent

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================
*/

#include "../include/drops.h"

/*
@header
    The drops_agent class starts a background drops agent.
@discuss
@end
*/

//  Structure of our class

struct _drops_agent_t {
    int filler;                         //  Unused
};


//  --------------------------------------------------------------------------
//  Constructor

drops_agent_t *
drops_agent_new (void)
{
    drops_agent_t *self = (drops_agent_t *) zmalloc (sizeof (drops_agent_t));
    return self;
}


//  -----------------------------------------------------------------
//  Destructor

void
drops_agent_destroy (drops_agent_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        drops_agent_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Selftest

int
drops_agent_test (bool verbose)
{
    printf (" * drops_agent: ");

    //  @selftest
    //  Simple create/destroy test
    drops_agent_t *self = drops_agent_new ();
    assert (self);
    drops_agent_destroy (&self);
    //  @end

    printf ("OK\n");
    return 0;
}
