/*  =========================================================================
    drops_agent - work with background drops agent

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================
*/

#ifndef __DROPS_AGENT_H_INCLUDED__
#define __DROPS_AGENT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _drops_agent_t drops_agent_t;

//  Background engine
void
    drops_agent_main (void *args, zctx_t *ctx, void *pipe);

//  Self test of this class
void
    drops_agent_test (bool verbose);

#ifdef __cplusplus
}
#endif

#endif
