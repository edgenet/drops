/*  =========================================================================
    drops.h - drops library API

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

#include "drops_agent.h"

#endif
