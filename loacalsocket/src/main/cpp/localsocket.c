//
// Created by pananfly on 20/9/21.
//
#include <jni.h>
#include "jni_register.h"
#include "jni_log.h"
#include "config.h"
#include "lsocket.h"
#include "jni_thread.h"
#include "j4a/j4a_base.h"
#include "local_socket_helper.h"
#include "LocalServerSocket.h"
#include "LocalSocket.h"
#include "LocalSocketAddress.h"
#include "OutputStream.h"

#include <cutils/sockets.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void* get_jni_instance(JNIEnv* env, jobject thiz, void* (get_func) (JNIEnv *env, jobject thiz))
{
    void* instance = (void *)(intptr_t)get_func(env, thiz);
    return instance;
}

void* set_jni_instance(JNIEnv* env, jobject thiz , void* instance, void* (get_func) (JNIEnv *env, jobject thiz), void (set_func) (JNIEnv *env, jobject thiz, jlong value))
{
    void* pre_instance = get_func(env, thiz);
    if(pre_instance)
    {
        pre_instance = NULL;
    }
    set_func(env, thiz, (intptr_t)instance);
    return pre_instance;
}

#ifndef JNI_CLASS_NAME
#define JNI_CLASS_NAME "package/unknown"
#endif
static const uint8_t HEAD[16] = {'P', 'A', 'N', 'S', 'O', 'C', 'K', 'E', 'T', 'H', 'E', 'A', 'D', '0', '0', '0'};
static const uint8_t TAIL[16] = {'P', 'A', 'N', 'S', 'O', 'C', 'K', 'E', 'T', 'T', 'A', 'I', 'L', '0', '0', '0'};

void intToByte(int i,uint8_t *bytes)
{
    //byte[] bytes = new byte[4];
    memset(bytes,0,sizeof(uint8_t) *  4);
    bytes[0] = (uint8_t) (i >> 24 & 0xFF);
    bytes[1] = (uint8_t) (i >> 16 & 0xFF);
    bytes[2] = (uint8_t) (i >> 8  & 0xFF);
    bytes[3] = (uint8_t) (i       & 0xFF);
}

int byteToInt(uint8_t bytes[])
{
    int sum = 0;
    if(sizeof(bytes) / sizeof(bytes[0]) < 4) {
        return sum;
    }
    sum  = bytes[3]         & 0xFF;
    sum |= (bytes[2] << 8) & 0xFF;
    sum |= (bytes[1] << 16) & 0xFF;
    sum |= (bytes[0] << 24) & 0xFF;
    return sum;
}

/**
 * So library implement, please notice of equipment compatible, these so files were pulled from a tablet device, maybe not applicable for your devices.
 * @param arg
 * @return
 */
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
    server_id = socket_local_server(_socket->socket_address, ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
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
    // make sure buf size less than 1024 * 1024, otherwise some devices will cause a crash. (I don't know this limit is affected same as binder or not.)
    // mock 1920*1080 video's stream push
    int buf_size = 1024 * 50 + 16 + 16; // 50k - I frame
    uint8_t * buffer  = malloc(buf_size);
    if(buffer)
    {
        memset(buffer, '1', buf_size);

        memcpy(buffer, HEAD, 16);
        memcpy(buffer + (buf_size - 16), TAIL, 16);
        intToByte(buf_size - 16 - 16 - 4, buffer + 16);
    }
    int buf_size2 = 1024 * 8 + 16 + 16; // 8k - P frame
    uint8_t * buffer2  = malloc(buf_size2);
    if(buffer2)
    {
        memset(buffer2, '2', buf_size2);
        memcpy(buffer2, HEAD, 16);
        memcpy(buffer2 + (buf_size2 - 16), TAIL, 16);
        intToByte(buf_size2 - 16 - 16 - 4, buffer2 + 16);
    }
    int count = 0;
    while (1)
    {
        P_LockMutex(_socket->mutex);
        if(!_socket->run_flag)
        {
            P_UnlockMutex(_socket->mutex);
            break;
        }
        LOGI("Server address:%s byte sent start.", _socket->socket_address);
        if( count % 30 == 0)
        {
            bytes_sent = buffer ? write(socket_id, buffer, buf_size) : -1;
            count = 1;
        }
        else
        {
            bytes_sent = buffer2 ? write(socket_id, buffer2, buf_size2) : -1;
        }
        count ++;
        LOGI("Server address:%s, byte sent: %d, count: %d.", _socket->socket_address, bytes_sent, count);
        P_UnlockMutex(_socket->mutex);
        usleep(2000 * 15);
    }
    if(buffer)
    {
        free(buffer);
    }
    if(buffer2)
    {
        free(buffer2);
    }
    close(socket_id);
    close(server_id);
    return ret;
}


// call back java local socket implement, just test run success.
int socket_run2(void* arg)
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
    int bytes_sent;
    jobject global_local_socket_client = NULL;
    jobject global_local_socket_output_stream = NULL;
    jobject  global_local_socket_server = J4AC_LocalServerSocket__LocalServerSocket__withCString__asGlobalRef__catchAll(env, _socket->socket_address);
    if(!global_local_socket_server)
    {
        ret = -3;
        return ret;
    }
    // Make sure buf size less than 1024 * 1024, otherwise some devices will cause a crash. (I don't know this limit is affected same as binder or not.)
    // ps: This implementation send more than 1024 * 1024 bytes won't crash on some devices(crash implement by so library).

    // mock 1920*1080 video's stream push
    int head_size = sizeof(HEAD)/ sizeof(HEAD[0]);
    int tail_size = sizeof(TAIL)/ sizeof(TAIL[0]);
    int len_size = 4;
    int buf_size = 1024 * 50 + head_size + tail_size + len_size; // 50k - I frame
    uint8_t * buffer  = malloc(buf_size);
    if(buffer)
    {
        memset(buffer, '1', buf_size);

        memcpy(buffer, HEAD, head_size);
        memcpy(buffer + (buf_size - tail_size), TAIL, tail_size);
        intToByte(buf_size - head_size - tail_size - len_size, buffer + head_size);
    }
    int buf_size2 = 1024 * 8 + head_size + tail_size + len_size; // 8k - P frame
    uint8_t * buffer2  = malloc(buf_size2);
    if(buffer2)
    {
        memset(buffer2, '2', buf_size2);
        memcpy(buffer2, HEAD, head_size);
        memcpy(buffer2 + (buf_size2 - tail_size), TAIL, tail_size);
        intToByte(buf_size2 - head_size - tail_size - len_size, buffer2 + head_size);
    }
    int count = 0;
    while (1)
    {

        P_LockMutex(_socket->mutex);
        if(!_socket->run_flag)
        {
            P_UnlockMutex(_socket->mutex);
            break;
        }
        P_UnlockMutex(_socket->mutex);
        // accept client(block thread).
        global_local_socket_client = J4AC_LocalServerSocket__accept__asGlobalRef__catchAll(env, global_local_socket_server);
        if(global_local_socket_client)
        {
            global_local_socket_output_stream = J4AC_LocalSocket__getOutputStream__asGlobalRef__catchAll(env, global_local_socket_client);
        }
        LOGI("Server(Java impl) address:%s accept socket start client:%d, ops:%d.", _socket->socket_address, global_local_socket_client != NULL, global_local_socket_output_stream != NULL);
        while(global_local_socket_output_stream)
        {
            P_LockMutex(_socket->mutex);
            if(!_socket->run_flag)
            {
                P_UnlockMutex(_socket->mutex);
                break;
            }
            LOGI("Server(Java impl) address:%s byte sent start.", _socket->socket_address);
            bool exception = false;
            if( count % 30 == 0)
            {
                jbyteArray write_buffer = J4A_NewByteArray__catchAll(env, buf_size);
                if(write_buffer && buffer)
                {
                    (*env)->SetByteArrayRegion(env, write_buffer, 0, (int)buf_size, (jbyte*) buffer);
                    J4AC_java_io_OutputStream__write(env, global_local_socket_output_stream, write_buffer, 0, buf_size);
                    exception = J4A_ExceptionCheck__catchAll(env);
                    bytes_sent = buf_size;
                }
                else
                {
                    bytes_sent = -1;
                }
                if(write_buffer)
                {
                    J4A_DeleteLocalRef__p(env, &write_buffer);
                }
                count = 1;
            }
            else
            {
                jbyteArray write_buffer = J4A_NewByteArray__catchAll(env, buf_size2);
                if(write_buffer && buffer)
                {
                    (*env)->SetByteArrayRegion(env, write_buffer, 0, (int)buf_size2, (jbyte*) buffer2);
                    J4AC_java_io_OutputStream__write(env, global_local_socket_output_stream, write_buffer, 0, buf_size2);
                    exception = J4A_ExceptionCheck__catchAll(env);
                    bytes_sent = buf_size2;
                }
                else
                {
                    bytes_sent = -1;
                }
                if(write_buffer)
                {
                    J4A_DeleteLocalRef__p(env, &write_buffer);
                }
            }
            count ++;
            LOGI("Server(Java impl) address:%s, byte sent: %d, count: %d.", _socket->socket_address, bytes_sent, count);
            P_UnlockMutex(_socket->mutex);
            if(exception)
            {
                break;
            }
            usleep(2000 * 15);
        }
        if(global_local_socket_client)
        {
            J4AC_LocalSocket__close__catchAll(env, global_local_socket_client);
            J4A_DeleteGlobalRef__p(env, &global_local_socket_client);
        }
        if(global_local_socket_output_stream)
        {
            J4AC_OutputStream__close__catchAll(env, global_local_socket_output_stream);
            J4A_DeleteGlobalRef__p(env, &global_local_socket_output_stream);
        }
        LOGI("Server(Java impl) address:%s accept socket end.", _socket->socket_address);
    }
    if(buffer)
    {
        free(buffer);
    }
    if(buffer2)
    {
        free(buffer2);
    }
    if(global_local_socket_server)
    {
        J4AC_LocalServerSocket__close__catchAll(env, global_local_socket_server);
        J4A_DeleteGlobalRef__p(env, &global_local_socket_server);
    }
    LOGI("Server(Java impl) address:%s thread end.", _socket->socket_address);
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
    JNI_Thread_OnLoad(vm, resered, JNI_VERSION_USE);
    int reg = jni_register(vm, resered, JNI_CLASS_NAME, g_methods, SIZELEM(g_methods));
    JNIEnv *env = NULL;
    if((*vm)->GetEnv(vm, (void **)&env , JNI_VERSION_USE) == JNI_OK)
    {
        J4A_LoadAll__catchAll(env);
    }
    return reg;
}

int test(JNIEnv *env, jobject thiz)
{
    LOGI("=======123========");
    return 0;
}


int startSocket(JNIEnv *env, jobject thiz, jstring path)
{
    int ret = 0;
    LSocket* socket = (LSocket *) get_jni_instance(env, thiz, (void *(*)(JNIEnv *, jobject)) J4AC_LocalSocketJNIHelper__mNativeInstance__get__catchAll);
    if(socket)
    {
        return 0;
    }
    char *address = (char *) (*env)->GetStringUTFChars(env, path, NULL);
    if (!address) {
        ret = -1;
        return ret;
    }
    socket = lsocket_create(address, socket_run2);
    if(!socket)
    {
        ret = -1;
        goto END;
    }
    LOGI("Start socket server address:%s .", address);
    set_jni_instance(env, thiz, socket, (void *(*)(JNIEnv *, jobject)) J4AC_LocalSocketJNIHelper__mNativeInstance__get__catchAll, J4AC_LocalSocketJNIHelper__mNativeInstance__set__catchAll);
    END:
    (*env)->ReleaseStringUTFChars(env, path, address);
    return ret;
}

int stopSocket(JNIEnv *env, jobject thiz)
{
    int ret = 0;
    LSocket* socket = (LSocket *) get_jni_instance(env, thiz, (void *(*)(JNIEnv *, jobject)) J4AC_LocalSocketJNIHelper__mNativeInstance__get__catchAll);
    if(!socket)
    {
        return -1;
    }
    LOGI("Stop socket server address:%s .", socket->socket_address);
    ret = lsocket_release(&socket);
    return ret;
}