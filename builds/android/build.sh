#!/bin/bash
#
# Build all dependencies with the proper options so that the NDK can
# find them.

MAKE_CORES=1
OUTPUT_DIR="`pwd`/output"

CPPFLAGS="-fPIC -I$OUTPUT_DIR/include"
LDFLAGS=-L$OUTPUT_DIR/lib
LIBS=-lgcc
CONFIGURE_FLAGS="--enable-static
                 --disable-shared
                 --host=arm-linux-androidabi
                 --prefix=$OUTPUT_DIR"

# libsodium
cd libsodium
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES check && make install
cd ..

# libzmq
cd libzmq
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES check && make install
cd ..

# CZMQ
cd czmq
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES check && make install
cd ..

# Zyre
cd zyre
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES check && make install
cd ..

exit 0
