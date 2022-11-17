#include "include/arguments.h"

#include "include/image.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void invalidArguments(int i, int argc)
{
    if(i + 1 > argc)
    {
        printf("Invalid arguments, check if arguments are ok\n");
        exit(0);
    }
    return;
}

ARGUMENTS parseArguments(int argc, const char** argv)
{
    if(argc < 2)
    {
        printf("%s --help\n", argv[0]);
        exit(0);
    }

    ARGUMENTS options;
    
    // make sure everything is 0
    options.input.length = 0;
    options.output.length = 0;

    options.play = 0;
    options.fps = 0.0;
    options.color_palete.data = NULL;
    options.color_palete.length = 0;
    options.clear_console = 0;

    options.threads = 0;

    options.verbose = 0;

    for (uint32_t i = 0; i < argc; i++)
    {
        const char* arg = argv[i];

        if(strcmp(arg, "--help") == 0)
        {
            printf("%s -i <input file/folder> -o <output file/folder>\n", argv[0]);
            printf("  (Optional) --help - Show this menu\n");
            printf("  -i <file/folder> - Input file or folder, if the input is a folder you can use multithread or play, only supports bitmap (.bmp) format\n");
            printf("  -o <file/folder> - Output file or folder, optional if you just want to play it, if you play the input it will not save any file\n");
            printf("  -p - Play the input file / folder, optional if you just want to convert it\n");
            printf("  -fps <number> - Set framerate in frames per second, example: 30, 24, 60, 23.976023976 (for cinema using float numbers use: \"1000 / (1001 / fps)\"), optional if you just want to convert it\n");
            printf("  (Optional) -palete <string> - Set custom color palete for ascii, the default is: \"%s\"\n", DEFAULT_CHAR_PALETTE);
            printf("  (Optional) -clear-console - Linux only, clear console before new frame draw, good for clean console to make it look better, bad for ssh connections\n");
            printf("  (Optional) -t <number> - Threads for paralel frame conversion, sometimes can be slow than single thread, recomended on slow computers or if the folder has plenty of files\n");
            printf("  (Optional) -v - Verbose output\n");

            exit(0);
        }

        if(strcmp(arg, "-i") == 0)
        {
            invalidArguments(i, argc);
            
            i++;
            const char* value = argv[i];

            options.input = string_from(value);

            continue;
        }
        if(strcmp(arg, "-o") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.output = string_from(value);

            continue;
        }

        if(strcmp(arg, "-p") == 0)
        {
            options.play = 1;

            continue;
        }
        if(strcmp(arg, "-fps") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.fps = atof(value);

            continue;
        }

        if(strcmp(arg, "-palete") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.color_palete = string_from(value);

            continue;
        }

        if(strcmp(arg, "-clear-console") == 0)
        {
            options.clear_console = 1;

            continue;
        }

        if(strcmp(arg, "-t") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.threads = atoi(value);

            continue;
        }

        if(strcmp(arg, "-v") == 0)
        {
            options.verbose = 1;

            continue;
        }
    }

    if(options.input.length == 0)
    {
        printf("The input (-i) is not optional\n");
        exit(0);
    }
    if (options.output.length == 0 && options.play == 0)
    {
        printf("The output is not optional if you will not play it\n");
        exit(0);
    }
    if (options.play == 1 && options.fps <= 0.0)
    {
        printf("The fps can't be lower than 0\n");
        exit(0);
    }

    return options;
}