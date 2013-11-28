LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libzmq-prebuilt
LOCAL_SRC_FILES := ./output/lib/libzmq.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libczmq-prebuilt
LOCAL_SRC_FILES := ./output/lib/libczmq.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libuuid-prebuilt
LOCAL_SRC_FILES := ./output/lib/libuuid.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libzyre-prebuilt
LOCAL_SRC_FILES := ./output/lib/libzyre.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libdrops-prebuilt
LOCAL_SRC_FILES := ./output/lib/libdrops.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := drops_jni
LOCAL_SRC_FILES := drops_jni.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/output/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../include
LOCAL_STATIC_LIBRARIES := libzmq-prebuilt libczmq-prebuilt libuuid-prebuilt libzyre-prebuilt libdrops-prebuilt
LOCAL_LD_LIBS := -llog -llibzmq-prebuilt -llibczmq-prebuilt -llibuuid-prebuilt -llibzyre-prebuilt -llibdrops-prebuilt
include $(BUILD_SHARED_LIBRARY)
