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

#ifndef J4A__android_net_LocalSocketAddress__H
#define J4A__android_net_LocalSocketAddress__H

#include "j4a/j4a_base.h"

jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress(JNIEnv *env, jstring name);
jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress__catchAll(JNIEnv *env, jstring name);
jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress__asGlobalRef__catchAll(JNIEnv *env, jstring name);
jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString(JNIEnv *env, const char *name_cstr__);
jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString__catchAll(JNIEnv *env, const char *name_cstr__);
jobject J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString__asGlobalRef__catchAll(JNIEnv *env, const char *name_cstr__);
jstring J4AC_android_net_LocalSocketAddress__getName(JNIEnv *env, jobject thiz);
jstring J4AC_android_net_LocalSocketAddress__getName__catchAll(JNIEnv *env, jobject thiz);
jstring J4AC_android_net_LocalSocketAddress__getName__asGlobalRef__catchAll(JNIEnv *env, jobject thiz);
const char *J4AC_android_net_LocalSocketAddress__getName__asCBuffer(JNIEnv *env, jobject thiz, char *out_buf, int out_len);
const char *J4AC_android_net_LocalSocketAddress__getName__asCBuffer__catchAll(JNIEnv *env, jobject thiz, char *out_buf, int out_len);
int J4A_loadClass__J4AC_android_net_LocalSocketAddress(JNIEnv *env);

#define J4A_HAVE_SIMPLE__J4AC_android_net_LocalSocketAddress

#define J4AC_LocalSocketAddress__LocalSocketAddress J4AC_android_net_LocalSocketAddress__LocalSocketAddress
#define J4AC_LocalSocketAddress__LocalSocketAddress__asGlobalRef__catchAll J4AC_android_net_LocalSocketAddress__LocalSocketAddress__asGlobalRef__catchAll
#define J4AC_LocalSocketAddress__LocalSocketAddress__catchAll J4AC_android_net_LocalSocketAddress__LocalSocketAddress__catchAll
#define J4AC_LocalSocketAddress__LocalSocketAddress__withCString J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString
#define J4AC_LocalSocketAddress__LocalSocketAddress__withCString__asGlobalRef__catchAll J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString__asGlobalRef__catchAll
#define J4AC_LocalSocketAddress__LocalSocketAddress__withCString__catchAll J4AC_android_net_LocalSocketAddress__LocalSocketAddress__withCString__catchAll
#define J4AC_LocalSocketAddress__getName J4AC_android_net_LocalSocketAddress__getName
#define J4AC_LocalSocketAddress__getName__asCBuffer J4AC_android_net_LocalSocketAddress__getName__asCBuffer
#define J4AC_LocalSocketAddress__getName__asCBuffer__catchAll J4AC_android_net_LocalSocketAddress__getName__asCBuffer__catchAll
#define J4AC_LocalSocketAddress__getName__asGlobalRef__catchAll J4AC_android_net_LocalSocketAddress__getName__asGlobalRef__catchAll
#define J4AC_LocalSocketAddress__getName__catchAll J4AC_android_net_LocalSocketAddress__getName__catchAll
#define J4A_loadClass__J4AC_LocalSocketAddress J4A_loadClass__J4AC_android_net_LocalSocketAddress

#endif//J4A__android_net_LocalSocketAddress__H
