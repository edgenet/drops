/*  =========================================================================
    drops - DROPS wrapper

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of zbroker, the ZeroMQ broker project.           
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           

    #################################################################
    #   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
    #   Please read the README.txt file                             #
    #################################################################
    =========================================================================
*/

#ifndef __DROPS_LIBRARY_H_INCLUDED__
#define __DROPS_LIBRARY_H_INCLUDED__

//  External dependencies
#include <zyre.h>

//  DROPS version macros for compile-time API detection

#define DROPS_VERSION_MAJOR 0
#define DROPS_VERSION_MINOR 0
#define DROPS_VERSION_PATCH 1

#define DROPS_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define DROPS_VERSION \
    DROPS_MAKE_VERSION(DROPS_VERSION_MAJOR, DROPS_VERSION_MINOR, DROPS_VERSION_PATCH)

#if defined (__WINDOWS__)
#   if defined LIBDROPS_STATIC
#       define DROPS_EXPORT
#   elif defined LIBDROPS_EXPORTS
#       define DROPS_EXPORT __declspec(dllexport)
#   else
#       define DROPS_EXPORT __declspec(dllimport)
#   endif
#else
#   define DROPS_EXPORT
#endif

//  Opaque class structures to allow forward references
typedef struct _drops_t drops_t;
#define DROPS_T_DEFINED


//  Public API classes

#endif
/*
    #################################################################
    #   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
    #   Please read the README.txt file in the model directory.     #
    #################################################################
*/    
