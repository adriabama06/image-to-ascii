#include "include/bmp.h"

#include "include/image.h"

#include "include/util.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dirent.h>

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

        struct CONVERT_ARGS_STRUCT* args = (struct CONVERT_ARGS_STRUCT*) malloc(sizeof(struct CONVERT_ARGS_STRUCT));

        args->bmp_files = bmp_files;

        args->from = 0;
        args->to = bmp_files->length;

        args->input_path = options.input_path;
        args->input_path_length = options.input;

        args->output_path = options.output_path;
        args->output_path_length = options.output;

        convert_multithread(args);
    }

    return 0;
}