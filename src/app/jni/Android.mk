LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := drops-jni
LOCAL_SRC_FILES := drops-jni.c
LOCAL_LD_LIBS := -lsodium -lzmq -lczmq -lzyre -ldrops

include $(BUILD_SHARED_LIBRARY)
