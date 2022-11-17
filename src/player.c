#include "include/player.h"

#include "include/bitmap.h"
#include "include/image.h"
#include "include/threads.h"
#include "include/time.h"
#include "include/console.h"
#include "include/string-util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef _WIN32
    #define custom_print(str) printf("%s\n", str)
#else
    #define custom_print(str) printf("%s", str)
#endif

void player(PLAYER_ARGS data)
{
    SYSTEM_TIME start_time;
    current_time(start_time);

    #ifdef __UINT64_TYPE__
        uint64_t start_time_precalc = time_to_ns(start_time);
    #endif

    SYSTEM_TIME current;

    uint32_t last_i = 0;
    uint32_t i = 0;
    while (i < data.frames.length)
    {
        current_time(current);

        #ifdef __UINT64_TYPE__
            i = ((time_to_ns(current) - start_time_precalc)) / data.framerate_ns;
        #else
            i = ((time_to_ns(current) - time_to_ns(start_time))) / data.framerate_ns;
        #endif

        if(i == last_i)
        {
            continue;
        }

        last_i = i;

        if(i == 0) i++; // make sure i != 0 because after this i do i - 1

        if (data.convert == 0)
        {
            custom_print(data.frames.strings[i - 1].data);

            continue;
        }
        
        STRING current_file = data.frames.strings[i - 1];

        STRING full_path;
        full_path.length = data.base_path.length + current_file.length;
        full_path.data = (char*) malloc(full_path.length * sizeof(char));

        strncpy(full_path.data, data.base_path.data, data.base_path.length);
        strncat(full_path.data, current_file.data, current_file.length);

        STRING frame;
        uint8_t isBitmap = endsWith(current_file.data, ".bmp");

        FILE* file_fp = isBitmap ? fopen(full_path.data, "rb") : fopen(full_path.data, "r");

        if(isBitmap)
        {
            BITMAP bmp;

            bitmap_decode(file_fp, &bmp);

            frame = image2ascii(bmp, data.color_palete);

            free(bmp.pixels);
        }
        else if (endsWith(current_file.data, ".txt"))
        {
            fseek(file_fp, 0, SEEK_END);
            frame.length = ftell(file_fp);

            frame.data = (char*) malloc(frame.length * sizeof(char));
            
            rewind(file_fp); // go to the start of the file

            fread(frame.data, sizeof(char), frame.length, file_fp);

            frame.data[frame.length] = '\0';
        }
        else
        {
            frame.data = (char*) malloc(250 * sizeof(char));
            frame.length = snprintf(frame.data, full_path.length, "Unknown what do at frame: %s", full_path.data);
        }

        fclose(file_fp);

        if(data.clear_console)
        {
            clear_console();
        }
        else
        {
            printf("\n");
        }

        custom_print(frame.data);

        if(data.verbose == 1)
        {
            printf("\n%s", current_file);
        }

        free(full_path.data);
        free(frame.data);
    }

    return;
}