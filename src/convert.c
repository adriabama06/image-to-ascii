#include "include/util.h"

#include "include/bmp.h"

#include "include/image.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void convert(char *input, char *output)
{
    BMP_DATA *bmp_data = bmp_read_data(input);

    IMAGE *raw_img = bmp_data_to_image(bmp_data);

    IMAGE *img = image_invert(raw_img);

    image_to_char_file(img, output);

    free(bmp_data);
    free(raw_img);
    free(img);
}

void *convert_multithread(void* __args)
{
    struct CONVERT_ARGS_STRUCT* args = (struct CONVERT_ARGS_STRUCT*) __args;

    for (uint32_t i = args->from; i < args->to; i++)
    {
        char* file = args->bmp_files->data[i];

        char* file_input = (char*) malloc((args->input_path_length + strlen(file) + 2) * sizeof(char));

        strcpy(file_input, args->input_path);

        #ifdef _WIN32
            if (endsWith(args->input_path, "\\") == 0)
            {
                strcat(file_input, "\\");
            }
        #else
            if (endsWith(args->input_path, "/") == 0)
            {
                strcat(file_input, "/");
            }
        #endif

        strcat(file_input, file);

        char* file_name_no_extension = get_filename(file);

        char* file_extension = (char*) malloc((strlen(file_name_no_extension) + strlen(".txt") + 2) * sizeof(char));

        strcpy(file_extension, file_name_no_extension);

        strcat(file_extension, ".txt");

        char* file_output = (char*) malloc((args->output_path_length + strlen(file_extension) + 2) * sizeof(char));

        strcpy(file_output, args->output_path);

        #ifdef _WIN32
            if (endsWith(args->output_path, "\\") == 0)
            {
                strcat(file_output, "\\");
            }
        #else
            if (endsWith(args->output_path, "/") == 0)
            {
                strcat(file_output, "/");
            }
        #endif

        strcat(file_output, file_extension);

        if(args->verbose)
        {
            printf("(%d > %d) - %s\n", i + 1, args->bmp_files->length, file);
            printf("%s -> %s\n", file_input, file_output);
        }

        convert(file_input, file_output);

        free(file_input);
        free(file_name_no_extension);
        free(file_extension);
        free(file_output);
    }

    return NULL;
}