
#ifndef P_MUTEX_H
#define P_MUTEX_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

#define P_MUTEX_TIMEDOUT  1
#define P_MUTEX_MAXWAIT   (~(uint32_t)0)

typedef struct P_mutex {
    pthread_mutex_t id;
} P_mutex;

typedef struct P_cond {
    pthread_cond_t id;
} P_cond;

P_mutex *P_CreateMutex(void);

void P_DestroyMutex(P_mutex *mutex);

void P_DestroyMutexP(P_mutex **mutex);

int P_LockMutex(P_mutex *mutex);

int P_UnlockMutex(P_mutex *mutex);


P_cond *P_CreateCond(void);

void P_DestroyCond(P_cond *cond);

void P_DestroyCondP(P_cond **cond);

int P_CondSignal(P_cond *cond);

int P_CondBroadcast(P_cond *cond);

int P_CondWaitTimeout(P_cond *cond, P_mutex *mutex, uint32_t ms);

int P_CondWait(P_cond *cond, P_mutex *mutex);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif //P_MUTEX_H
