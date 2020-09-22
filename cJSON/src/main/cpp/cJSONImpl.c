
#include <jni.h>
#include "cJSON.h"
#ifndef SIZELEM
#define SIZELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif
#define JNI_CLASS_CJSON_NAME "com/pananfly/cjson/cJSONImpl"

void cJSON_ParseJSON(JNIEnv *env, jobject thiz);

static JNINativeMethod g_methods[] = {
        {
                "parseJSON",
                "()V",
                (void *) cJSON_ParseJSON
        }
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *resered)
{
    JNIEnv *env = NULL;
    if((*vm)->GetEnv(vm, (void **)&env , JNI_VERSION_1_4) != JNI_OK)
    {
        return -1;
    }
    jclass clazz = (*env)->FindClass(env, JNI_CLASS_CJSON_NAME);
    (*env)->RegisterNatives(env, clazz, g_methods, SIZELEM(g_methods));
    (*env)->DeleteLocalRef(env, clazz);
    return JNI_VERSION_1_4;
}

void cJSON_ParseJSON(JNIEnv *env, jobject thiz)
{

}
