#默认的头文件路径是LOCAL_PATH
#LOCAL_C_INCLUDES  可选变量，表示头文件的搜索路径
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := jnimode
LOCAL_MODULE_FILENAME := libjnimode
LOCAL_SRC_FILES := com_android_suning_jnimode_jnibase_JniUtils.cpp \
SunningDes.cpp \
blowfish.cpp \
md5.cpp \
Utils.cpp

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)
