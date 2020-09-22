
#include "p_thread.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "jni_log.h"

#ifdef __ANDROID__
    #include <jni_thread.h>
#include <jni.h>

#endif

static void *P_RunThread(void *data)
{
    P_Thread *thread = data;
    pthread_setname_np(pthread_self() , thread->name);
    thread->retval = thread->func(thread->data);
#ifdef __ANDROID__
    JNI_Thread_DetachThreadEnv();
#endif
    return NULL;
}


P_Thread *P_CreateThread(P_Thread *thread , int( *fn)(void *) , void *data , const char *name)
{
    thread->func = fn;
    thread->data = data;
    strlcpy(thread->name , name , sizeof(thread->name) - 1);
    int retval = pthread_create(&thread->id , NULL , P_RunThread, thread);
    if(retval)
        return NULL;
    return thread;
}

int P_SetThreadPriority(P_ThreadPriority priority)
{
    struct sched_param sched;
    int policy;
    pthread_t thread = pthread_self();

    if (pthread_getschedparam(thread, &policy, &sched) < 0) {
        LOGE("pthread_getschedparam() failed");
        return -1;
    }
    if (priority == P_THREAD_PRIORITY_LOW) {
        sched.sched_priority = sched_get_priority_min(policy);
    } else if (priority == P_THREAD_PRIORITY_HIGH) {
        sched.sched_priority = sched_get_priority_max(policy);
    } else {
        int min_priority = sched_get_priority_min(policy);
        int max_priority = sched_get_priority_max(policy);
        sched.sched_priority = (min_priority + (max_priority - min_priority) / 2);
    }
    if (pthread_setschedparam(thread, policy, &sched) < 0) {
        LOGE("pthread_setschedparam() failed");
        return -1;
    }
    return 0;
}

void P_JoinThread(P_Thread *thread , int *status)
{
    if(!thread)
        return;

    thread->retval = pthread_join(thread->id , NULL);

    if(status)
        *status = thread->retval;
}

void P_DetachThread(P_Thread *thread)
{
    if(!thread)
        return;
    pthread_detach(thread->id);
}
