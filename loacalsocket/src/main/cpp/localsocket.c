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
#define ADDRESS "\077889900"

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
//    jobject weak_thiz = (jobject)av_acquire_get_weak_thiz(handler);
    int socket_fd;
    int address_length;
    struct sockaddr_un server_address, client_address;
    int bytes_received, bytes_sent, integer_buffer;

    if ((socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        LOGE("server: socket");
        ret = -3;
        return ret;
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    address_length = sizeof(server_address.sun_family) + sizeof(ADDRESS) - 1;
    memcpy(server_address.sun_path, ADDRESS , sizeof(ADDRESS) - 1);
//    strcpy(client_address.sun_path, "#UdsClient");
//    client_address.sun_path[0] = 0;

    if (bind(socket_fd,
             (const struct sockaddr *) &server_address,
             address_length) < 0)
    {
        close(socket_fd);
        LOGE("server: bind");
        ret = -4;
        return ret;
    }

    while (1)
    {
        P_LockMutex(_socket->mutex);
        if(!_socket->run_flag)
        {
            P_UnlockMutex(_socket->mutex);
            break;
        }
        integer_buffer = 10;
        sendto(socket_fd,
               &integer_buffer,
               sizeof(integer_buffer),
               0,
               (struct sockaddr *) &client_address,
               address_length);
        P_UnlockMutex(_socket->mutex);
        usleep(2000 * 10);
    }
    close(socket_fd);
    return ret;
}

int initLocalSocket(char* path)
{
    int ret = 0;
//    int socket = android_get_control_socket(path);
//    if(socket == -1)
//    {
//        ret = socket;
//        goto END;
//    }
//    listen(socket, 1);

    int socket_fd;
    int address_length;
    struct sockaddr_un server_address, client_address;
    int bytes_received, bytes_sent, integer_buffer;

    if ((socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("server: socket");
        return -1;
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    address_length = sizeof(server_address.sun_family) + sizeof(ADDRESS) - 1;
    memcpy(server_address.sun_path, ADDRESS , sizeof(ADDRESS) - 1);
//    strcpy(client_address.sun_path, "#UdsClient");
//    client_address.sun_path[0] = 0;

    if (bind(socket_fd,
             (const struct sockaddr *) &server_address,
             address_length) < 0)
    {
        close(socket_fd);
        perror("server: bind");
        return -1;
    }

    for (;;)
    {
        bytes_received = recvfrom(socket_fd,
                                  &integer_buffer,
                                  sizeof(integer_buffer),
                                  0,
                                  (struct sockaddr *) &client_address,
                                  &address_length);

        if(bytes_received != sizeof(integer_buffer))
        {
            printf("Error: recvfrom - %d.\n", bytes_received);
        } else {
            printf("received: %d.\n", integer_buffer);

            integer_buffer += 10;

            bytes_sent = sendto(socket_fd,
                                &integer_buffer,
                                sizeof(integer_buffer),
                                0,
                                (struct sockaddr *) &client_address,
                                address_length);
        }
    }

    close(socket_fd);

    END:
    return ret;
}

int client()
{
    int socket_fd;
    struct sockaddr_un server_address, client_address;
    int bytes_received, bytes_sent, integer_buffer;
    socklen_t address_length = sizeof(struct sockaddr_un);

    if((socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("client: socket");
        return -1;
    }

    memset(&client_address, 0, sizeof(client_address));
    client_address.sun_family = AF_UNIX;
    strcpy(client_address.sun_path, "#UdsClient");
    client_address.sun_path[0] = 0;

    if(bind(socket_fd,
            (const struct sockaddr *) &client_address,
            address_length) < 0)
    {
        perror("client: bind");
        return -1;
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "#UdsServer");
    server_address.sun_path[0] = 0;

    integer_buffer = 1;

    for (;;)
    {
        bytes_sent = sendto(socket_fd,
                            &integer_buffer,
                            sizeof(integer_buffer),
                            0,
                            (struct sockaddr *) &server_address,
                            address_length);

        bytes_received = recvfrom(socket_fd,
                                  &integer_buffer,
                                  sizeof(integer_buffer),
                                  0,
                                  (struct sockaddr *) &server_address,
                                  &address_length);

        if (bytes_received != sizeof(integer_buffer))
        {
            printf("Error: recvfrom - %d.\n", bytes_received);
            return -1;
        }

        printf("received: %d\n", integer_buffer);

        integer_buffer += 1;

        sleep(10);
    }

    close(socket_fd);
    return 0;
}

int test(JNIEnv *env, jobject thiz);
int startSocket(JNIEnv *env, jobject thiz);
int stopSocket(JNIEnv *env, jobject thiz);

static JNINativeMethod g_methods[] = {
        {
                "test",
                "()I",
                (void *) test
        },
        {
                "startSocket",
                "()I",
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
    return jni_register(vm, resered, JNI_CLASS_NAME, g_methods, SIZELEM(g_methods));
}

int test(JNIEnv *env, jobject thiz)
{
    LOGI("=======123========");
    return 0;
}


int startSocket(JNIEnv *env, jobject thiz)
{
    int ret = 0;
    if(_socket)
    {
        return 0;
    }
    _socket = lsocket_create(socket_run);
    if(!_socket)
    {
        ret = -1;
    }
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