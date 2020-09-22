
#ifndef JNI_REGISTER_H
#define JNI_REGISTER_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <jni.h>

#ifndef SIZELEM
#define SIZELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

int jni_register(JavaVM *vm, void *resered, const char *class_name, const JNINativeMethod *methods,
                 const int method_size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif