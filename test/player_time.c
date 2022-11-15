#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


void player(int framerate_ms, int end)
{
    struct timeval start_time;
    struct timeval current;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < end;)
    {
        gettimeofday(&current, NULL);

        i = (((current.tv_sec * 1000000) + current.tv_usec) - ((start_time.tv_sec * 1000000) + start_time.tv_usec)) / framerate_ms;
    }
    
}

int main(int argc, const char** argv)
{
    player(1000000 / 30, 60);

    return 0;
}