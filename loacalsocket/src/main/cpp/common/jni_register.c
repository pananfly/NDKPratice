
#include "jni_register.h"

int jni_register(JavaVM *vm, void *resered, const char* class_name, const JNINativeMethod* methods, const int method_size)
{
    JNIEnv *env = NULL;
    if(!class_name || !methods)
    {
        return -1;
    }
    if((*vm)->GetEnv(vm, (void **)&env , JNI_VERSION_1_4) != JNI_OK)
    {
        return -1;
    }
    jclass clazz = (*env)->FindClass(env, class_name);
    (*env)->RegisterNatives(env, clazz, methods, method_size);
    (*env)->DeleteLocalRef(env, clazz);
    return JNI_VERSION_1_4;
}