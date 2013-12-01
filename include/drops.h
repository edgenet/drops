/*  =========================================================================
    drops - start/stop drops file sharing service

    Copyright the Contributors as noted in the AUTHORS file.
    This file is part of edgenet and is licensed per the LICENSE file.
    =========================================================================*/

#ifndef __DROPS_H_INCLUDED__
#define __DROPS_H_INCLUDED__

//  DROPS version macros for compile-time API detection

#define DROPS_VERSION_MAJOR 0
#define DROPS_VERSION_MINOR 0
#define DROPS_VERSION_PATCH 1

#define DROPS_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define DROPS_VERSION \
    DROPS_MAKE_VERSION(DROPS_VERSION_MAJOR, DROPS_VERSION_MINOR, DROPS_VERSION_PATCH)

#include <czmq.h>
#if CZMQ_VERSION < 20100
#   error "drops needs CZMQ/2.1.0 or later"
#endif

#include <zyre.h>
#if ZYRE_VERSION < 10100
#   error "drops needs Zyre/1.1.0 or later"
#endif

//  The public API consists of the "drops_t" class

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _drops_t drops_t;

//  @interface
//  Constructor, creates a new drops agent
CZMQ_EXPORT drops_t *
    drops_new (const char *path);

//  Destructor, ends and destroys a drops service
CZMQ_EXPORT void
    drops_destroy (drops_t **self_p);

//  Receive next message from drops agent
CZMQ_EXPORT zmsg_t *
    drops_recv (drops_t *self);

//  Return handle to the drops agent, for polling
CZMQ_EXPORT void *
    drops_socket (drops_t *self);

//  Self test of this class
CZMQ_EXPORT void
    drops_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif


#endif
