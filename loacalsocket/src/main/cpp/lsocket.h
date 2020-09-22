
#ifndef LSOCKET_H
#define LSOCKET_H
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include "p_mutex.h"
#include "p_thread.h"

typedef struct LSocket {
    P_Thread *socket_thread;
    P_Thread _socket_thread;

    P_mutex *mutex;
    P_cond *cond;
    int32_t run_flag;
} LSocket;

LSocket* lsocket_create(int32_t (*thread_func)(void *));
int32_t lsocket_release(LSocket **pSocket);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif //LSOCKET_H
