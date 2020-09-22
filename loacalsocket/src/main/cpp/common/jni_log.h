
#ifndef JNI_LOG_H
#define JNI_LOG_H

#include <android/log.h>
#include "config.h"
#ifndef JNI_LOG_TAG
#define JNI_LOG_TAG "JNI_LOG"
#endif

#define LOG_UNKNOW ANDROID_LOG_UNKNOW
#define LOG_VERBOSE ANDROID_LOG_VERBOSE
#define LOG_DEBUG ANDROID_LOG_DEBUG
#define LOG_INFO ANDROID_LOG_INFO
#define LOG_WARN ANDROID_LOG_WARN
#define LOG_ERROR ANDROID_LOG_ERROR
#define LOG_FATAL ANDROID_LOG_FATAL

#define LOG(level , TAG , ...) ((void)__android_log_print(level , TAG , __VA_ARGS__))

#define LOGV(...) LOG(LOG_VERBOSE , JNI_LOG_TAG , __VA_ARGS__)
#define LOGD(...) LOG(LOG_DEBUG , JNI_LOG_TAG , __VA_ARGS__)
#define LOGI(...) LOG(LOG_INFO , JNI_LOG_TAG , __VA_ARGS__)
#define LOGW(...) LOG(LOG_WARN , JNI_LOG_TAG , __VA_ARGS__)
#define LOGE(...) LOG(LOG_ERROR , JNI_LOG_TAG , __VA_ARGS__)
#define LOGF(...) LOG(LOG_FATAL , JNI_LOG_TAG , __VA_ARGS__)

#endif //JNI_LOG_H
