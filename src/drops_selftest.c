/*  =========================================================================
    drops_selftest - run self tests

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================
*/

#include "../include/drops.h"

int main (int argc, char *argv [])
{
    bool verbose;
    if (argc == 2 && streq (argv [1], "-v"))
        verbose = true;
    else
        verbose = false;

    printf ("Running self tests...\n");
    drops_agent_test (verbose);
    printf ("Tests passed OK\n");
    return 0;
}
