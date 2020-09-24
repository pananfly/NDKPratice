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

#include "local_socket_helper.h"

typedef struct J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper {
    jclass id;

    jfieldID field_mNativeInstance;
} J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper;
static J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper;

jlong J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__get(JNIEnv *env, jobject thiz)
{
    return (*env)->GetLongField(env, thiz, class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.field_mNativeInstance);
}

jlong J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__get__catchAll(JNIEnv *env, jobject thiz)
{
    jlong ret_value = J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__get(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}

void J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__set(JNIEnv *env, jobject thiz, jlong value)
{
    (*env)->SetLongField(env, thiz, class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.field_mNativeInstance, value);
}

void J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__set__catchAll(JNIEnv *env, jobject thiz, jlong value)
{
    J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper__mNativeInstance__set(env, thiz, value);
    J4A_ExceptionCheck__catchAll(env);
}

int J4A_loadClass__J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper(JNIEnv *env)
{
    int         ret                   = -1;
    const char *J4A_UNUSED(name)      = NULL;
    const char *J4A_UNUSED(sign)      = NULL;
    jclass      J4A_UNUSED(class_id)  = NULL;
    int         J4A_UNUSED(api_level) = 0;

    if (class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.id != NULL)
        return 0;

    sign = JNI_CLASS_NAME;
    class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.id == NULL)
        goto fail;

    class_id = class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.id;
    name     = "mNativeInstance";
    sign     = "J";
    class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.field_mNativeInstance = J4A_GetFieldID__catchAll(env, class_id, name, sign);
    if (class_J4AC_com_pananfly_loacalsocket_LocalSocketJNIHelper.field_mNativeInstance == NULL)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", sign);
    ret = 0;
fail:
    return ret;
}
