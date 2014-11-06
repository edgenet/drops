/*  =========================================================================
    drops - DROPS wrapper


    #################################################################
    #   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
    #   Please read the README.txt file                             #
    #################################################################
    =========================================================================
*/

#ifndef __DROPS_H_INCLUDED__
#define __DROPS_H_INCLUDED__

//  External dependencies
#include <czmq.h>
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
