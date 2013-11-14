# drops

**drops** is a simple file sharer. At this stage it's a prototype concept for edgenet.

The use case is as follows:

* A number of mobile devices are connected to the same WiFi cell
* All the devices are running the drops application
* We monitor a specific directory on each device, say /sdcard/DCIM
* When a new file is created in that directory, we share that file with all peers

The test scenario is taking a photo with one device and seeing that photo appear on another.

## Goals

The main goal of this prototype concept is to get a minimum end-to-end example of a cell-based application, that is:

* Two phones connected over a single WiFi hotspot, where
* One of the phones is acting as access point
* Content created on either phone will flow to the other

The drops application will be an Android application that wraps up a drops service written in C. So additional goals are:

* To test the tool chain for building Android apps that wrap C libraries in JNI layers
* To test and demo Zyre, the library that does discovery and messaging over WiFi
* To give contributors some code to get their teeth into.

## Technical Design

The drops app has these layers (I guess):

* An Android application, "drops", which provides a start/stop UI
* A C library, "libdrops", which does the heavy lifting
* A JNI layer that wraps libdrops and makes it available to the Java code

The libdrops library has these primary dependencies:

* Zyre (libzyre) from http://zyre.com.
* CZMQ (libczmq) from http://czmq.zeromq.org
* ZeroMQ v4 (libzmq) from http://zeromq.org
* Sodium (libsodium) from https://github.com/jedisct1/libsodium

