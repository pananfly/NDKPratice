/*
 * Copyright (C) 2015 Zhang Rui <bbcallen@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * https://github.com/Bilibili/jni4android
 * This file is automatically generated by jni4android, do not modify.
 */

#include "OutputStream.h"

typedef struct J4AC_java_io_OutputStream {
    jclass id;

    jmethodID method_write;
    jmethodID method_flush;
    jmethodID method_close;
} J4AC_java_io_OutputStream;
static J4AC_java_io_OutputStream class_J4AC_java_io_OutputStream;

void J4AC_java_io_OutputStream__write(JNIEnv *env, jobject thiz, jbyteArray b, jint off, jint len)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_java_io_OutputStream.method_write, b, off, len);
}

void J4AC_java_io_OutputStream__write__catchAll(JNIEnv *env, jobject thiz, jbyteArray b, jint off, jint len)
{
    J4AC_java_io_OutputStream__write(env, thiz, b, off, len);
    J4A_ExceptionCheck__catchAll(env);
}

void J4AC_java_io_OutputStream__flush(JNIEnv *env, jobject thiz)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_java_io_OutputStream.method_flush);
}

void J4AC_java_io_OutputStream__flush__catchAll(JNIEnv *env, jobject thiz)
{
    J4AC_java_io_OutputStream__flush(env, thiz);
    J4A_ExceptionCheck__catchAll(env);
}

void J4AC_java_io_OutputStream__close(JNIEnv *env, jobject thiz)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_java_io_OutputStream.method_close);
}

void J4AC_java_io_OutputStream__close__catchAll(JNIEnv *env, jobject thiz)
{
    J4AC_java_io_OutputStream__close(env, thiz);
    J4A_ExceptionCheck__catchAll(env);
}

int J4A_loadClass__J4AC_java_io_OutputStream(JNIEnv *env)
{
    int         ret                   = -1;
    const char *J4A_UNUSED(name)      = NULL;
    const char *J4A_UNUSED(sign)      = NULL;
    jclass      J4A_UNUSED(class_id)  = NULL;
    int         J4A_UNUSED(api_level) = 0;

    if (class_J4AC_java_io_OutputStream.id != NULL)
        return 0;

    sign = "java/io/OutputStream";
    class_J4AC_java_io_OutputStream.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_java_io_OutputStream.id == NULL)
        goto fail;

    class_id = class_J4AC_java_io_OutputStream.id;
    name     = "write";
    sign     = "([BII)V";
    class_J4AC_java_io_OutputStream.method_write = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_java_io_OutputStream.method_write == NULL)
        goto fail;

    class_id = class_J4AC_java_io_OutputStream.id;
    name     = "flush";
    sign     = "()V";
    class_J4AC_java_io_OutputStream.method_flush = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_java_io_OutputStream.method_flush == NULL)
        goto fail;

    class_id = class_J4AC_java_io_OutputStream.id;
    name     = "close";
    sign     = "()V";
    class_J4AC_java_io_OutputStream.method_close = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_java_io_OutputStream.method_close == NULL)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "java.io.OutputStream");
    ret = 0;
fail:
    return ret;
}
