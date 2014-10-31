#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################
lib_LTLIBRARIES = libdrops.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdrops.pc

include_HEADERS = \
    ../include/drops.h \
    drops_agent.h

libdrops_la_SOURCES = \
    platform.h \
    drops.c \
    drops_agent.c

AM_CFLAGS = -g
AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = drops_selftest
drops_selftest_LDADD = libdrops.la
drops_selftest_SOURCES = drops_selftest.c

libdrops_la_LDFLAGS = \
  -version-info @LTVER@ \
  $(LIBTOOL_EXTRA_LDFLAGS)

if ON_MINGW
libdrops_la_LDFLAGS += \
  -no-undefined
  -avoid-version
endif

TESTS = drops_selftest

#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################
