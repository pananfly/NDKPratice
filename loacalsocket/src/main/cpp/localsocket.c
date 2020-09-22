//
// Created by pananfly on 20/9/21.
//
#include <jni.h>
#include "jni_register.h"
#include "jni_log.h"
#include "config.h"
#include "lsocket.h"
#include "jni_thread.h"

#include <cutils/sockets.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef JNI_CLASS_NAME
#define JNI_CLASS_NAME "package/unknown"
#endif
#define ADDRESS "com.pananfly.localsocket/test1"

static LSocket* _socket;

int socket_run(void* arg)
{
    JNIEnv *env = NULL;
    int32_t ret = 0;
    if(JNI_Thread_SetupThreadEnv(&env) != JNI_OK)
    {
        ret = -1;
        return ret;
    }
    LSocket *_socket = (LSocket *) arg;
    if(!_socket)
    {
        ret = -2;
        return ret;
    }

    P_SetThreadPriority(P_THREAD_PRIORITY_HIGH);
    prctl(PR_SET_NAME , _socket->socket_thread->name);
    int server_id, socket_id, bytes_sent;
    server_id = socket_local_server(ADDRESS, ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
    if(server_id < 0)
    {
        LOGI("Server socket_local_server invalid: %d.", server_id);
        return server_id;
    }
    while((socket_id = accept(server_id, NULL, NULL)) < 0)
    {
        P_LockMutex(_socket->mutex);
        if(!_socket->run_flag)
        {
            P_UnlockMutex(_socket->mutex);
            break;
        }
        P_UnlockMutex(_socket->mutex);
    }
    char buffer[]  = {"this message from c server \n"};
    while (1)
    {
        P_LockMutex(_socket->mutex);
        if(!_socket->run_flag)
        {
            P_UnlockMutex(_socket->mutex);
            break;
        }
        bytes_sent = write(socket_id, buffer, strlen(buffer));
        LOGI("Server byte sent: %d.", bytes_sent);
        P_UnlockMutex(_socket->mutex);
        usleep(2000 * 100);
    }
    close(socket_id);
    close(server_id);
    return ret;
}

int test(JNIEnv *env, jobject thiz);
int startSocket(JNIEnv *env, jobject thiz, jstring path);
int stopSocket(JNIEnv *env, jobject thiz);

static JNINativeMethod g_methods[] = {
        {
                "test",
                "()I",
                (void *) test
        },
        {
                "startSocket",
                "(Ljava/lang/String;)I",
                (void *) startSocket
        },
        {
                "stopSocket",
                "()I",
                (void *) stopSocket
        },
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *resered)
{
    JNI_Thread_OnLoad(vm, resered);
    return jni_register(vm, resered, JNI_CLASS_NAME, g_methods, SIZELEM(g_methods));
}

int test(JNIEnv *env, jobject thiz)
{
    LOGI("=======123========");
    return 0;
}


int startSocket(JNIEnv *env, jobject thiz, jstring path)
{
    int ret = 0;
    if(_socket)
    {
        return 0;
    }
    char *address = (char *) (*env)->GetStringUTFChars(env, path, NULL);
    if (!address) {
        ret = -1;
        return ret;
    }
    _socket = lsocket_create(address, socket_run);
    if(!_socket)
    {
        ret = -1;
    }
    (*env)->ReleaseStringUTFChars(env, path, address);
    return ret;
}

int stopSocket(JNIEnv *env, jobject thiz)
{
    int ret = 0;
    if(!_socket)
    {
        return -1;
    }
    ret = lsocket_release(&_socket);
    return ret;
}