#!/bin/bash
#
# Clones all the dependencies, or pulls from master if they already
# exist. Run from builds/android

# libuuid
if [ -d "e2fsprogs" ]; then
  cd e2fsprogs
  git pull
  cd ..
else
  git clone https://git.kernel.org/pub/scm/fs/ext2/e2fsprogs.git
fi

# not used yet
if [ -d "libsodium" ]; then
  cd libsodium
  git pull
  cd ..
else
  git clone https://github.com/jedisct1/libsodium
fi

if [ -d "libzmq" ]; then
  cd libzmq
  git pull
  cd ..
else
  git clone https://github.com/zeromq/libzmq
fi

if [ -d "czmq" ]; then
  cd czmq
  git pull
  cd ..
else
  git clone https://github.com/zeromq/czmq
fi

if [ -d "zyre" ]; then
  cd zyre
  git pull
  cd ..
else
  git clone https://github.com/zeromq/zyre
fi

exit 0
