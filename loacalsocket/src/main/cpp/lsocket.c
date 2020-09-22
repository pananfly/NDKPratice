
#include "lsocket.h"


LSocket* lsocket_create(const char* address, int32_t (*thread_func)(void *))
{
    LSocket* socket = NULL;
    if(!thread_func || !address) {
        goto END;
    }
    socket = malloc(sizeof(LSocket));
    if(!socket)
    {
        goto END;
    }
    socket->run_flag = 1;
    socket->socket_address = malloc(strlen(address));
    if(!socket->socket_address)
    {
        lsocket_release(&socket);
        goto END;
    }
    strcpy(socket->socket_address, address);
    socket->mutex = P_CreateMutex();
    if(!socket->mutex)
    {
        lsocket_release(&socket);
        goto END;
    }
    socket->cond = P_CreateCond();
    if(!socket->mutex)
    {
        lsocket_release(&socket);
        goto END;
    }
    socket->socket_thread = P_CreateThread(&socket->_socket_thread, thread_func, socket, "N_SOCKET_THREAD");
    if(!socket->socket_thread)
    {
        lsocket_release(&socket);
        goto END;
    }
    END:
    return socket;
}

int32_t lsocket_release(LSocket **pSocket)
{
    int32_t ret = 0;
    LSocket* socket = *pSocket;
    if(!socket)
    {
        ret = -1;
        goto END;
    }
    if(socket->socket_address)
    {
        free(socket->socket_address);
        socket->socket_address = NULL;
    }
    if(socket->mutex && socket->cond)
    {
        P_LockMutex(socket->mutex);
        socket->run_flag = 0;
        P_CondSignal(socket->cond);
        P_UnlockMutex(socket->mutex);
    }
    if(socket->socket_thread)
    {
        P_JoinThread(socket->socket_thread, NULL);
    }
    if(socket->mutex)
    {
        P_DestroyMutexP(&socket->mutex);
    }
    if(socket->mutex)
    {
        P_DestroyCondP(&socket->cond);
    }
    *pSocket = NULL;
    END:
    return ret;
}