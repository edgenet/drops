#!/bin/bash
#
# Build all dependencies with the proper options so that the NDK can
# find them.

export MAKE_CORES=8
export OUTPUT="`pwd`/../../src/app/jni/output"
export PATH=$TOOLCHAIN/bin:$PATH

export CC="arm-linux-androideabi-gcc"
export CXX="arm-linux-androideabi-g++"

export LIBS="-lgnustl_shared"
export LDFLAGS="-L$OUTPUT/lib"
export CFLAGS="-fPIC -I$OUTPUT/include"
export CPPFLAGS="-fPIC -I$OUTPUT/include"
export CONFIGURE_FLAGS="--enable-static=yes --enable-shared=no --host=arm-linux-androideabi --prefix=$OUTPUT"

# ZeroMQ
cd ./libzmq
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES && make install
cd ..

# CZMQ
cd ./czmq
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES && make install
cd ..

# libuuid
cd ./e2fsprogs
./configure $CONFIGURE_FLAGS && cd ./lib/uuid && make -j$MAKE_CORES && make install
cd ../../..

# Zyre
cd ./zyre
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES && make install
cd ..

# Drops
cd ../..
./autogen.sh && ./configure $CONFIGURE_FLAGS && make -j$MAKE_CORES && make install
cd ..

exit 0
