#ifdef _WIN32
    #include <windows.h>

    typedef HANDLE thread_t;
#else
    #include <pthread.h>

    typedef pthread_t thread_t;
#endif

void thread_create(thread_t* thread_id, void* (*thread_func)(void*), void* arg);

void thread_join(thread_t thread_id);