#ifdef _WIN32
    #include <windows.h>

    typedef SYSTEMTIME SYSTEM_TIME;
    
    #define time_to_ns(t) (((t.wHour * 60 * 60 * 1000) + (t.wMinute * 60 * 1000) + (t.wSecond * 1000) + t.wMilliseconds) * 1000)
    #define current_time(t) GetSystemTime(&t)
#else
    #include <sys/time.h>
    #include <time.h>

    typedef struct timeval SYSTEM_TIME;

    #define time_to_ns(t) ((t.tv_sec * 1000000) + t.tv_usec)
    #define current_time(t) gettimeofday(&t, NULL)
#endif