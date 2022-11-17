#include "include/threads.h"

void thread_create(thread_t* thread_id, void* (*thread_func)(void*), void* arg)
{
    #ifdef _WIN32
        *thread_id = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread_func, arg, 0, NULL);
    #else
        pthread_create(thread_id, NULL, thread_func, arg);
    #endif

    return;
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