#include "include/threads.h"

int thread_create(thread_t* thread_id, void* (*thread_func)(void*), void* arg)
{
    #ifdef _WIN32
        *thread_id = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread_func, arg, 0, NULL);

        return 0;
    #else
        return pthread_create(thread_id, NULL, thread_func, arg);
    #endif
}

void thread_join(thread_t thread_id)
{
    #ifdef _WIN32
        WaitForSingleObject(thread_id, INFINITE);
    #else
        pthread_join(thread_id, NULL);
    #endif

    return;
}