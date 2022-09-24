#include "include/bmp.h"

#include "include/image.h"

#include "include/util.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dirent.h>

void convert(char* input, char* output)
{
    BMP_DATA* bmp_data = bmp_read_data(input);
    
    IMAGE* raw_img = bmp_data_to_image(bmp_data);

    IMAGE* img = image_invert(raw_img);

    image_to_char_file(img, output);

    free(bmp_data);
    free(raw_img);
    free(img);
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("%s --help\n", argv[0]);
        return 0;
    }

    struct PROGRAM_USER_INPUT options = parseArguments(argc, argv);

    if(options.is_input_folder == 0)
    {
        convert(options.input_path, options.output_path);
    }
    else
    {
        STRING_ARRAY* bmp_files = search_bmp(options.input_path);

        for (uint32_t i = 0; i < bmp_files->length; i++)
        {
            char* file = bmp_files->data[i];

            printf("(%d > %d) - %s\n", i, bmp_files->length, file);

            char* file_input = (char*) malloc((options.input + strlen(file) + 2) * sizeof(char));

            strcpy(file_input, options.input_path);

            #ifdef _WIN32
                if(endsWith(options.input_path, "\\") == 0)
                {
                    strcat(file_input, "\\");
                }
            #else
                if(endsWith(options.input_path, "/") == 0)
                {
                    strcat(file_input, "/");
                }
            #endif
            

            strcat(file_input, file);

            char* file_name_no_extension = get_filename(file);

            char* file_extension = malloc((strlen(file_name_no_extension) + strlen(".txt") + 2) * sizeof(char));

            strcpy(file_extension, file_name_no_extension);

            strcat(file_extension, ".txt");

            char* file_output = (char*) malloc((options.output + strlen(file_extension) + 2) * sizeof(char));

            strcpy(file_output, options.output_path);

            #ifdef _WIN32
                if(endsWith(options.output_path, "\\") == 0)
                {
                    strcat(file_output, "\\");
                }
            #else
                if(endsWith(options.output_path, "/") == 0)
                {
                    strcat(file_output, "/");
                }
            #endif

            strcat(file_output, file_extension);

            printf("%s -> %s\n", file_input, file_output);

            convert(file_input, file_output);

            free(file_input);
            free(file_name_no_extension);
            free(file_extension);
            free(file_output);
        }
    }

    return 0;
}