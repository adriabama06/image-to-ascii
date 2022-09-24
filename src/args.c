#include "include/util.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void invalidArguments(int i, int argc)
{
    if(i + 1 > argc)
    {
        printf("Invalid arguments, check if arguments are ok\n");
        exit(0);
    }
    return;
}

struct PROGRAM_USER_INPUT parseArguments(int argc, const char *argv[])
{
    struct PROGRAM_USER_INPUT options;

    options.input = 0;
    options.output = 0;
    options.multithread = 0;

    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];
        
        if(strcmp(arg, "--help") == 0)
        {
            printf("%s -i <input file/folder> -o <output file/folder>\n", argv[0]);
            printf("  (Optional) --help - Show this help menu\n");
            printf("  -i - Input file or folder, ONLY .bmp FILE SUPPORT\n");
            printf("  -o - Output file or folder if the input is a folder\n");
            printf("  (Optional) -t - Define number of threads for multithread, only work if the input is a folder\n");

            exit(0);
        }

        if(strcmp(arg, "-i") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.input = strlen(value);

            options.input_path = (char*) malloc(options.input * sizeof(char) + 1);

            strcpy(options.input_path, value);

            options.is_input_folder = isDir(options.input_path);

            continue;
        }

        if(strcmp(arg, "-o") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.output = strlen(value);

            options.output_path = (char*) malloc(options.output * sizeof(char) + 1);

            strcpy(options.output_path, value);

            options.is_output_folder = isDir(options.output_path);

            continue;
        }

        if(strcmp(arg, "-t") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.multithread = atoi(value);
            
            continue;
        }
    }

    if(options.input == 0 || options.output == 0)
    {
        printf("Please wrtie a input and output\n");

        exit(0);
    }

    if(options.is_input_folder != options.is_output_folder)
    {
        printf("If the input is a file, the output need to be a file, and the same for folders\n");
    
        exit(0);
    }

    return options;
}