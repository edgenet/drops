LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := drops-jni
LOCAL_SRC_FILES := drops-jni.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../zyre/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../czmq/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../libzmq/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../libsodium/src/libsodium/include/
LOCAL_LD_LIBS := -lsodium -lzmq -lczmq -lzyre -ldrops

include $(BUILD_SHARED_LIBRARY)
