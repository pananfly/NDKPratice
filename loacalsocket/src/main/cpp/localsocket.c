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
static const uint8_t HEAD[16] = {'P', 'A', 'N', 'S', 'O', 'C', 'K', 'E', 'T', 'H', 'E', 'A', 'D', '0', '0', '0'};
static const uint8_t TAIL[16] = {'P', 'A', 'N', 'S', 'O', 'C', 'K', 'E', 'T', 'T', 'A', 'I', 'L', '0', '0', '0'};

static LSocket* _socket;
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
    // mock 1920*1080 video's stream push
    int buf_size = 20 + 16 + 16; // 50k - I frame
    uint8_t * buffer  = malloc(buf_size);
    if(buffer)
    {
        memset(buffer, '1', buf_size);

        memcpy(buffer, HEAD, 16);
        memcpy(buffer + (buf_size - 16), TAIL, 16);
        intToByte(buf_size - 16 - 16 - 4, buffer + 16);
//        buffer[buf_size - 1] = '\n';
    }
    int buf_size2 = 10 + 16 + 16; // 8k - P frame
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
        LOGI("Server address:%s byte sent 1.", _socket->socket_address);
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