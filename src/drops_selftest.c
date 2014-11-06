/*  =========================================================================
    drops_selftest.c - run selftests

    Runs all selftests.

    -------------------------------------------------------------------------

    #################################################################
    #   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
    #   Please read the README.txt file in the model directory.     #
    #################################################################
    =========================================================================
*/

#include "../include/drops.h"
#include "drops_classes.h"

int
main (int argc, char *argv [])
{
    bool verbose;
    if (argc == 2 && streq (argv [1], "-v"))
        verbose = true;
    else
        verbose = false;

    printf ("Running DROPS selftests...\n");

    drops_test (verbose); 
    drops_agent_test (verbose); 

    printf ("Tests passed OK\n");
    return 0;
}
/*
    #################################################################
    #   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
    #   Please read the README.txt file in the model directory.     #
    #################################################################
*/
