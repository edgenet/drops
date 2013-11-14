/*  =========================================================================
    drops_agent - work with background drops agent

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================*/

#ifndef __DROPS_AGENT_H_INCLUDED__
#define __DROPS_AGENT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _drops_agent_t drops_agent_t;

//  @interface
//  Create a new drops_agent
drops_agent_t *
    drops_agent_new (void);

//  Destroy the drops_agent
void
    drops_agent_destroy (drops_agent_t **self_p);

//  Self test of this class
int
    drops_agent_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
