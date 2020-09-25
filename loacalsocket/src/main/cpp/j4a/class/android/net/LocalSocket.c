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

#include "LocalSocket.h"

typedef struct J4AC_android_net_LocalSocket {
    jclass id;

    jmethodID constructor_LocalSocket;
    jmethodID method_bind;
    jmethodID method_getLocalSocketAddress;
    jmethodID method_getInputStream;
    jmethodID method_getOutputStream;
    jmethodID method_close;
    jmethodID method_shutdownInput;
    jmethodID method_shutdownOutput;
    jmethodID method_setReceiveBufferSize;
    jmethodID method_getReceiveBufferSize;
    jmethodID method_setSoTimeout;
    jmethodID method_getSoTimeout;
    jmethodID method_setSendBufferSize;
    jmethodID method_getSendBufferSize;
    jmethodID method_getRemoteSocketAddress;
    jmethodID method_isConnected;
    jmethodID method_isClosed;
    jmethodID method_isBound;
    jmethodID method_isOutputShutdown;
    jmethodID method_isInputShutdown;
    jmethodID method_connect;
} J4AC_android_net_LocalSocket;
static J4AC_android_net_LocalSocket class_J4AC_android_net_LocalSocket;

jobject J4AC_android_net_LocalSocket__LocalSocket(JNIEnv *env, jint sockType)
{
    return (*env)->NewObject(env, class_J4AC_android_net_LocalSocket.id, class_J4AC_android_net_LocalSocket.constructor_LocalSocket, sockType);
}

jobject J4AC_android_net_LocalSocket__LocalSocket__catchAll(JNIEnv *env, jint sockType)
{
    jobject ret_object = J4AC_android_net_LocalSocket__LocalSocket(env, sockType);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject J4AC_android_net_LocalSocket__LocalSocket__asGlobalRef__catchAll(JNIEnv *env, jint sockType)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_net_LocalSocket__LocalSocket__catchAll(env, sockType);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

void J4AC_android_net_LocalSocket__bind(JNIEnv *env, jobject thiz, jobject bindpoint)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_bind, bindpoint);
}

void J4AC_android_net_LocalSocket__bind__catchAll(JNIEnv *env, jobject thiz, jobject bindpoint)
{
    J4AC_android_net_LocalSocket__bind(env, thiz, bindpoint);
    J4A_ExceptionCheck__catchAll(env);
}

jobject J4AC_android_net_LocalSocket__getLocalSocketAddress(JNIEnv *env, jobject thiz)
{
    return (*env)->CallObjectMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getLocalSocketAddress);
}

jobject J4AC_android_net_LocalSocket__getLocalSocketAddress__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object = J4AC_android_net_LocalSocket__getLocalSocketAddress(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getLocalSocketAddress__asGlobalRef__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_net_LocalSocket__getLocalSocketAddress__catchAll(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getInputStream(JNIEnv *env, jobject thiz)
{
    return (*env)->CallObjectMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getInputStream);
}

jobject J4AC_android_net_LocalSocket__getInputStream__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object = J4AC_android_net_LocalSocket__getInputStream(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getInputStream__asGlobalRef__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_net_LocalSocket__getInputStream__catchAll(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getOutputStream(JNIEnv *env, jobject thiz)
{
    return (*env)->CallObjectMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getOutputStream);
}

jobject J4AC_android_net_LocalSocket__getOutputStream__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object = J4AC_android_net_LocalSocket__getOutputStream(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getOutputStream__asGlobalRef__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_net_LocalSocket__getOutputStream__catchAll(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

void J4AC_android_net_LocalSocket__close(JNIEnv *env, jobject thiz)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_close);
}

void J4AC_android_net_LocalSocket__close__catchAll(JNIEnv *env, jobject thiz)
{
    J4AC_android_net_LocalSocket__close(env, thiz);
    J4A_ExceptionCheck__catchAll(env);
}

void J4AC_android_net_LocalSocket__shutdownInput(JNIEnv *env, jobject thiz)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_shutdownInput);
}

void J4AC_android_net_LocalSocket__shutdownInput__catchAll(JNIEnv *env, jobject thiz)
{
    J4AC_android_net_LocalSocket__shutdownInput(env, thiz);
    J4A_ExceptionCheck__catchAll(env);
}

void J4AC_android_net_LocalSocket__shutdownOutput(JNIEnv *env, jobject thiz)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_shutdownOutput);
}

void J4AC_android_net_LocalSocket__shutdownOutput__catchAll(JNIEnv *env, jobject thiz)
{
    J4AC_android_net_LocalSocket__shutdownOutput(env, thiz);
    J4A_ExceptionCheck__catchAll(env);
}

void J4AC_android_net_LocalSocket__setReceiveBufferSize(JNIEnv *env, jobject thiz, jint size)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_setReceiveBufferSize, size);
}

void J4AC_android_net_LocalSocket__setReceiveBufferSize__catchAll(JNIEnv *env, jobject thiz, jint size)
{
    J4AC_android_net_LocalSocket__setReceiveBufferSize(env, thiz, size);
    J4A_ExceptionCheck__catchAll(env);
}

jint J4AC_android_net_LocalSocket__getReceiveBufferSize(JNIEnv *env, jobject thiz)
{
    return (*env)->CallIntMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getReceiveBufferSize);
}

jint J4AC_android_net_LocalSocket__getReceiveBufferSize__catchAll(JNIEnv *env, jobject thiz)
{
    jint ret_value = J4AC_android_net_LocalSocket__getReceiveBufferSize(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}

void J4AC_android_net_LocalSocket__setSoTimeout(JNIEnv *env, jobject thiz, jint n)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_setSoTimeout, n);
}

void J4AC_android_net_LocalSocket__setSoTimeout__catchAll(JNIEnv *env, jobject thiz, jint n)
{
    J4AC_android_net_LocalSocket__setSoTimeout(env, thiz, n);
    J4A_ExceptionCheck__catchAll(env);
}

jint J4AC_android_net_LocalSocket__getSoTimeout(JNIEnv *env, jobject thiz)
{
    return (*env)->CallIntMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getSoTimeout);
}

jint J4AC_android_net_LocalSocket__getSoTimeout__catchAll(JNIEnv *env, jobject thiz)
{
    jint ret_value = J4AC_android_net_LocalSocket__getSoTimeout(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}

void J4AC_android_net_LocalSocket__setSendBufferSize(JNIEnv *env, jobject thiz, jint n)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_setSendBufferSize, n);
}

void J4AC_android_net_LocalSocket__setSendBufferSize__catchAll(JNIEnv *env, jobject thiz, jint n)
{
    J4AC_android_net_LocalSocket__setSendBufferSize(env, thiz, n);
    J4A_ExceptionCheck__catchAll(env);
}

jint J4AC_android_net_LocalSocket__getSendBufferSize(JNIEnv *env, jobject thiz)
{
    return (*env)->CallIntMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getSendBufferSize);
}

jint J4AC_android_net_LocalSocket__getSendBufferSize__catchAll(JNIEnv *env, jobject thiz)
{
    jint ret_value = J4AC_android_net_LocalSocket__getSendBufferSize(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}

jobject J4AC_android_net_LocalSocket__getRemoteSocketAddress(JNIEnv *env, jobject thiz)
{
    return (*env)->CallObjectMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_getRemoteSocketAddress);
}

jobject J4AC_android_net_LocalSocket__getRemoteSocketAddress__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object = J4AC_android_net_LocalSocket__getRemoteSocketAddress(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject J4AC_android_net_LocalSocket__getRemoteSocketAddress__asGlobalRef__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_net_LocalSocket__getRemoteSocketAddress__catchAll(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

jboolean J4AC_android_net_LocalSocket__isConnected(JNIEnv *env, jobject thiz)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_isConnected);
}

jboolean J4AC_android_net_LocalSocket__isConnected__catchAll(JNIEnv *env, jobject thiz)
{
    jboolean ret_value = J4AC_android_net_LocalSocket__isConnected(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

jboolean J4AC_android_net_LocalSocket__isClosed(JNIEnv *env, jobject thiz)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_isClosed);
}

jboolean J4AC_android_net_LocalSocket__isClosed__catchAll(JNIEnv *env, jobject thiz)
{
    jboolean ret_value = J4AC_android_net_LocalSocket__isClosed(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

jboolean J4AC_android_net_LocalSocket__isBound(JNIEnv *env, jobject thiz)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_isBound);
}

jboolean J4AC_android_net_LocalSocket__isBound__catchAll(JNIEnv *env, jobject thiz)
{
    jboolean ret_value = J4AC_android_net_LocalSocket__isBound(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

jboolean J4AC_android_net_LocalSocket__isOutputShutdown(JNIEnv *env, jobject thiz)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_isOutputShutdown);
}

jboolean J4AC_android_net_LocalSocket__isOutputShutdown__catchAll(JNIEnv *env, jobject thiz)
{
    jboolean ret_value = J4AC_android_net_LocalSocket__isOutputShutdown(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

jboolean J4AC_android_net_LocalSocket__isInputShutdown(JNIEnv *env, jobject thiz)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_isInputShutdown);
}

jboolean J4AC_android_net_LocalSocket__isInputShutdown__catchAll(JNIEnv *env, jobject thiz)
{
    jboolean ret_value = J4AC_android_net_LocalSocket__isInputShutdown(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

void J4AC_android_net_LocalSocket__connect(JNIEnv *env, jobject thiz, jobject endpoint, jint timeout)
{
    (*env)->CallVoidMethod(env, thiz, class_J4AC_android_net_LocalSocket.method_connect, endpoint, timeout);
}

void J4AC_android_net_LocalSocket__connect__catchAll(JNIEnv *env, jobject thiz, jobject endpoint, jint timeout)
{
    J4AC_android_net_LocalSocket__connect(env, thiz, endpoint, timeout);
    J4A_ExceptionCheck__catchAll(env);
}

int J4A_loadClass__J4AC_android_net_LocalSocket(JNIEnv *env)
{
    int         ret                   = -1;
    const char *J4A_UNUSED(name)      = NULL;
    const char *J4A_UNUSED(sign)      = NULL;
    jclass      J4A_UNUSED(class_id)  = NULL;
    int         J4A_UNUSED(api_level) = 0;

    if (class_J4AC_android_net_LocalSocket.id != NULL)
        return 0;

    sign = "android/net/LocalSocket";
    class_J4AC_android_net_LocalSocket.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_android_net_LocalSocket.id == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "<init>";
    sign     = "(I)V";
    class_J4AC_android_net_LocalSocket.constructor_LocalSocket = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.constructor_LocalSocket == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "bind";
    sign     = "(Landroid/net/LocalSocketAddress;)V";
    class_J4AC_android_net_LocalSocket.method_bind = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_bind == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getLocalSocketAddress";
    sign     = "()Landroid/net/LocalSocketAddress;";
    class_J4AC_android_net_LocalSocket.method_getLocalSocketAddress = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getLocalSocketAddress == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getInputStream";
    sign     = "()Ljava/io/InputStream;";
    class_J4AC_android_net_LocalSocket.method_getInputStream = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getInputStream == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getOutputStream";
    sign     = "()Ljava/io/OutputStream;";
    class_J4AC_android_net_LocalSocket.method_getOutputStream = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getOutputStream == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "close";
    sign     = "()V";
    class_J4AC_android_net_LocalSocket.method_close = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_close == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "shutdownInput";
    sign     = "()V";
    class_J4AC_android_net_LocalSocket.method_shutdownInput = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_shutdownInput == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "shutdownOutput";
    sign     = "()V";
    class_J4AC_android_net_LocalSocket.method_shutdownOutput = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_shutdownOutput == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "setReceiveBufferSize";
    sign     = "(I)V";
    class_J4AC_android_net_LocalSocket.method_setReceiveBufferSize = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_setReceiveBufferSize == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getReceiveBufferSize";
    sign     = "()I";
    class_J4AC_android_net_LocalSocket.method_getReceiveBufferSize = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getReceiveBufferSize == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "setSoTimeout";
    sign     = "(I)V";
    class_J4AC_android_net_LocalSocket.method_setSoTimeout = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_setSoTimeout == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getSoTimeout";
    sign     = "()I";
    class_J4AC_android_net_LocalSocket.method_getSoTimeout = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getSoTimeout == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "setSendBufferSize";
    sign     = "(I)V";
    class_J4AC_android_net_LocalSocket.method_setSendBufferSize = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_setSendBufferSize == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getSendBufferSize";
    sign     = "()I";
    class_J4AC_android_net_LocalSocket.method_getSendBufferSize = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getSendBufferSize == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "getRemoteSocketAddress";
    sign     = "()Landroid/net/LocalSocketAddress;";
    class_J4AC_android_net_LocalSocket.method_getRemoteSocketAddress = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_getRemoteSocketAddress == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "isConnected";
    sign     = "()Z";
    class_J4AC_android_net_LocalSocket.method_isConnected = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_isConnected == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "isClosed";
    sign     = "()Z";
    class_J4AC_android_net_LocalSocket.method_isClosed = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_isClosed == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "isBound";
    sign     = "()Z";
    class_J4AC_android_net_LocalSocket.method_isBound = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_isBound == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "isOutputShutdown";
    sign     = "()Z";
    class_J4AC_android_net_LocalSocket.method_isOutputShutdown = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_isOutputShutdown == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "isInputShutdown";
    sign     = "()Z";
    class_J4AC_android_net_LocalSocket.method_isInputShutdown = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_isInputShutdown == NULL)
        goto fail;

    class_id = class_J4AC_android_net_LocalSocket.id;
    name     = "connect";
    sign     = "(Landroid/net/LocalSocketAddress;I)V";
    class_J4AC_android_net_LocalSocket.method_connect = J4A_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_net_LocalSocket.method_connect == NULL)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "android.net.LocalSocket");
    ret = 0;
fail:
    return ret;
}
