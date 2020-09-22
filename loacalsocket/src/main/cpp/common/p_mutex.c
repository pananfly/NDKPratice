
#include "p_mutex.h"

P_mutex *P_CreateMutex(void)
{
    P_mutex *mutex;
    mutex = (P_mutex *) calloc(sizeof(P_mutex) , 1);
    if(!mutex)
    {
        return mutex;
    }
    if(pthread_mutex_init(&mutex->id , NULL) != 0)
    {
        free(mutex);
        mutex = NULL;
    }
    return mutex;
}

void P_DestroyMutex(P_mutex *mutex)
{
    if(mutex) {
        pthread_mutex_destroy(&mutex->id);
        free(mutex);
    }
}

void P_DestroyMutexP(P_mutex **mutex)
{
    if(mutex) {
        P_DestroyMutex(*mutex);
        *mutex = NULL;
    }
}

int P_LockMutex(P_mutex *mutex)
{
    if(!mutex)
    {
        return -1;
    }
    return pthread_mutex_lock(&mutex->id);
}

int P_UnlockMutex(P_mutex *mutex)
{
    if(!mutex)
    {
        return -1;
    }
    return pthread_mutex_unlock(&mutex->id);
}

P_cond *P_CreateCond(void)
{
    P_cond *cond;
    cond = (P_cond *) calloc(sizeof(P_cond) , 1);
    if(!cond)
    {
        return cond;
    }
    if(pthread_cond_init(&cond->id , NULL) != 0)
    {
        free(cond);
        cond = NULL;
    }
    return cond;
}

void P_DestroyCond(P_cond *cond)
{
    if(cond)
    {
        pthread_cond_destroy(&cond->id);
        free(cond);
    }
}

void P_DestroyCondP(P_cond **cond)
{
    if(cond)
    {
        P_DestroyCond(*cond);
        *cond = NULL;
    }
}

int P_CondSignal(P_cond *cond)
{
    if(!cond)
    {
        return -1;
    }
    return pthread_cond_signal(&cond->id);
}

int P_CondBroadcast(P_cond *cond)
{
    if(!cond)
    {
        return -1;
    }
    return pthread_cond_broadcast(&cond->id);
}

int P_CondWaitTimeout(P_cond *cond, P_mutex *mutex , uint32_t ms)
{
    int ret = 0;
    struct timeval delta;
    struct timespec abstime;
    if(!mutex || !cond)
    {
        return -1;
    }

    gettimeofday(&delta , NULL);

    abstime.tv_sec = delta.tv_sec + (ms / 1000);
    abstime.tv_nsec = (delta.tv_usec + (ms % 1000) * 1000) * 1000;
    if(abstime.tv_nsec > 1000000000)
    {
        abstime.tv_sec += 1;
        abstime.tv_nsec -= 1000000000;
    }

    while (1)
    {
        ret = pthread_cond_timedwait(&cond->id , &mutex->id , &abstime);
        if(ret == 0)
        {
            return 0;
        }
        else if(ret == EINTR)
        {
            continue;
        }
        else if(ret == ETIMEDOUT)
        {
            return P_MUTEX_TIMEDOUT;
        }
        else
        {
            break;
        }
    }
    return -1;
}

int P_CondWait(P_cond *cond, P_mutex *mutex)
{
    if(!cond || !mutex)
    {
        return -1;
    }
    return pthread_cond_wait(&cond->id , &mutex->id);
}