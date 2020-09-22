
#ifndef JNI_THREAD_H
#define JNI_THREAD_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <jni.h>
#include <pthread.h>

JNIEXPORT jint JNICALL JNI_Thread_OnLoad(JavaVM *vm, void *reserved);

JNIEXPORT void JNICALL JNI_Thread_OnUnLoad(JavaVM *vm, void *reserved);

jint JNI_Thread_SetupThreadEnv(JNIEnv **env);

void JNI_Thread_DetachThreadEnv();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif //JNI_THREAD_H
