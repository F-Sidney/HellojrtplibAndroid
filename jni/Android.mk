LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE  := jthread
LOCAL_SRC_FILES := libjthread.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE  := jrtplib
LOCAL_SRC_FILES := libjrtplib.a
LOCAL_STATIC_LIBRARIES := jthread
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := HelloJni
LOCAL_SRC_FILES := HelloJni.cpp
LOCAL_STATIC_LIBRARIES := jthread jrtplib
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)