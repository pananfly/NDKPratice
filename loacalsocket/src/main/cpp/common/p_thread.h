
#ifndef P_THREAD_H
#define P_THREAD_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <pthread.h>
#include <sys/prctl.h>

typedef enum {
    P_THREAD_PRIORITY_LOW,
    P_THREAD_PRIORITY_NORMAL,
    P_THREAD_PRIORITY_HIGH
} P_ThreadPriority;

typedef struct P_Thread {
    pthread_t id;

    int (*func)(void *);

    void *data;
    char name[32];
    int retval;
} P_Thread;

P_Thread *P_CreateThread(P_Thread *thread, int( *fn)(void *), void *data, const char *name);

int P_SetThreadPriority(P_ThreadPriority priority);

void P_JoinThread(P_Thread *thread, int *status);

void P_DetachThread(P_Thread *thread);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif //P_THREAD_H
