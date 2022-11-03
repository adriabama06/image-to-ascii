#include "include/bmp.h"

#include "include/image.h"

#include "include/util.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dirent.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <pthread.h>
#endif

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("%s --help\n", argv[0]);
        return 0;
    }

    PROGRAM_USER_INPUT options = parseArguments(argc, argv);

    if(options.is_input_folder == 0)
    {
        convert(options.input_path, options.output_path);
    }
    else
    {
        STRING_ARRAY* bmp_files = search_bmp(options.input_path);

        if (options.multithread == 0)
        {
            struct CONVERT_ARGS_STRUCT* args = (struct CONVERT_ARGS_STRUCT*) malloc(sizeof(struct CONVERT_ARGS_STRUCT));

            args->verbose = options.verbose;

            args->bmp_files = bmp_files;

            args->from = 0;
            args->to = bmp_files->length;

            args->input_path = options.input_path;
            args->input_path_length = options.input;

            args->output_path = options.output_path;
            args->output_path_length = options.output;

            convert_multithread(args);
        }
        else
        {
            #ifdef _WIN32
                HANDLE* threads = (HANDLE*) calloc(options.multithread, sizeof(HANDLE));
            #else
                pthread_t threads[options.multithread];
            #endif

            for (int i = 0; i < options.multithread; i++)
            {
                struct CONVERT_ARGS_STRUCT* args = (struct CONVERT_ARGS_STRUCT*) malloc(sizeof(struct CONVERT_ARGS_STRUCT));

                args->verbose = options.verbose;

                args->bmp_files = bmp_files;

                args->from = (i * (bmp_files->length / options.multithread));
                args->to = ((i + 1) * (bmp_files->length / options.multithread));

                args->input_path = options.input_path;
                args->input_path_length = options.input;

                args->output_path = options.output_path;
                args->output_path_length = options.output;

                #ifdef _WIN32
                    threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) convert_multithread, args, 0, NULL);
                #else
                    pthread_create(&threads[i], NULL, convert_multithread, args);
                #endif
            }
            
            for(int i = 0; i < options.multithread; i++) {
                #ifdef _WIN32
                    WaitForSingleObject(threads[i], INFINITE);
                #else
                    pthread_join(threads[i], NULL);
                #endif
            }
        }
    }

    return 0;
}