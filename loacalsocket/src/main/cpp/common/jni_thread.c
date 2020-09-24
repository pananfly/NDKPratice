
#include "jni_thread.h"

static JavaVM* ava_jni_thread_jvm;
static pthread_key_t ava_thread_key;
static pthread_once_t ava_key_once = PTHREAD_ONCE_INIT;

JNIEXPORT jint JNICALL JNI_Thread_OnLoad(JavaVM *vm , void *reserved, int jni_version)
{
    int ret = 0;
    ava_jni_thread_jvm = vm;
    JNIEnv *env = NULL;
    if((*vm)->GetEnv(vm , &env , jni_version) != JNI_OK)
    {
        return -1;
    }
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_Thread_OnUnLoad(JavaVM *vm , void *reserved)
{

}

static void JNI_ThreadDestroyed(void* value)
{
    JNIEnv *env = (JNIEnv*) value;
    if (env != NULL) {
//        ALOGE("%s: [%d] didn't call SDL_JNI_DetachThreadEnv() explicity\n", __func__, (int)gettid());
        (*ava_jni_thread_jvm)->DetachCurrentThread(ava_jni_thread_jvm);
        pthread_setspecific(ava_thread_key, NULL);
    }
}

static void ava_thread_func()
{
    pthread_key_create(&ava_thread_key, JNI_ThreadDestroyed);
}

jint JNI_Thread_SetupThreadEnv(JNIEnv **p_env)
{
    JavaVM *jvm = ava_jni_thread_jvm;
    if (!jvm) {
//        ALOGE("SDL_JNI_GetJvm: AttachCurrentThread: NULL jvm");
        return -1;
    }

    pthread_once(&ava_key_once, ava_thread_func);

    JNIEnv *env = (JNIEnv*) pthread_getspecific(ava_thread_key);
    if (env) {
        *p_env = env;
        return 0;
    }

    if ((*jvm)->AttachCurrentThread(jvm, &env, NULL) == JNI_OK) {
        pthread_setspecific(ava_thread_key, env);
        *p_env = env;
        return 0;
    }

    return -1;
}

void JNI_Thread_DetachThreadEnv()
{
    JavaVM *jvm = ava_jni_thread_jvm;

    pthread_once(&ava_key_once, ava_thread_key);

    JNIEnv *env = pthread_getspecific(ava_thread_key);
    if (!env)
        return;
    pthread_setspecific(ava_thread_key, NULL);
    if (!jvm)
        return;
    if ((*jvm)->DetachCurrentThread(jvm) == JNI_OK)
        return;

    return;
}