#include "include/quick.h"

#include "include/bitmap.h"
#include "include/image.h"
#include "include/string-util.h"
#include "include/fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void convert_to_file(const char* input, const char* output, char* color_palete)
{
    FILE* bmp_fd = fopen(input, "rb");
    
    BITMAP bmp;

    bitmap_decode(bmp_fd, &bmp);

    fclose(bmp_fd);

    STRING ascii = image2ascii(bmp, color_palete != NULL ? color_palete : DEFAULT_CHAR_PALETTE);

    FILE* result_fd = fopen(output, "w");

    fwrite(ascii.data, sizeof(char), ascii.length, result_fd);

    fclose(result_fd);

    free(bmp.pixels);
    free(ascii.data);

    return;
}

void* convert_multiple_to_file(void* __data)
{
    CONVERT_MULTIPLE_TO_FILE_ARGS* data = (CONVERT_MULTIPLE_TO_FILE_ARGS*) __data;

    for (uint32_t i = data->from; i < data->to; i++)
    {
        STRING file = data->files.strings[i];

        STRING input = path_join(data->options.input, file);

        char* filename = get_filename(file.data);

        STRING output_file;

        output_file.length = strlen(filename) + strlen(OUTPUT_EXTENSION);

        output_file.data = (char*) malloc(output_file.length * sizeof(char));

        strcpy(output_file.data, filename);
        strcat(output_file.data, OUTPUT_EXTENSION);

        STRING output = path_join(data->options.output, output_file);

        convert_to_file(input.data, output.data, data->options.color_palete.data);

        if(data->options.verbose == 1)
        {
            printf("%d - %s => %s\n", i + 1, input.data, output.data);
        }

        free(input.data);
        free(filename);
        free(output_file.data);
        free(output.data);
    }
    

    return NULL;
}