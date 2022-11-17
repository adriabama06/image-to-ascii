#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/arguments.h"
#include "include/bitmap.h"
#include "include/image.h"
#include "include/fs.h"
#include "include/threads.h"
#include "include/player.h"
#include "include/time.h"
#include "include/quick.h"

int main(int argc, const char** argv)
{
    ARGUMENTS options = parseArguments(argc, argv);

    if(options.play == 0)
    {
        if(!existDir(options.input.data))
        {
            convert_to_file(options.input.data, options.output.data, options.color_pallete.data);

            return 0;
        }

        if(options.threads == 0)
        {
            CONVERT_MULTIPLE_TO_FILE_ARGS data;

            data.files = search_files_by_suffix(options.input.data, ".bmp");

            data.from = 0;

            data.to = data.files.length;

            data.options = options;

            convert_multiple_to_file((void*) &data);

            return 0;
        }

        // do this for Win and Linux compatibility without use #ifdef ...
        thread_t* threads = (thread_t*) calloc(options.threads, sizeof(thread_t));

        STRING_ARRAY files = search_files_by_suffix(options.input.data, ".bmp");

        for (uint32_t i = 0; i < options.threads; i++)
        {
            CONVERT_MULTIPLE_TO_FILE_ARGS* data = (CONVERT_MULTIPLE_TO_FILE_ARGS*) malloc(sizeof(CONVERT_MULTIPLE_TO_FILE_ARGS));

            data->files = files;

            data->from = (i * (files.length / options.threads));

            data->to = ((i + 1) * (files.length / options.threads));

            data->options = options;

            thread_create(&threads[i], convert_multiple_to_file, (void*) data);
        }

        for (uint32_t i = 0; i < options.threads; i++)
        {
            thread_join(threads[i]);
        }
    }
    else
    {
        PLAYER_ARGS args;

        args.base_path = options.input;

        STRING_ARRAY frames = search_files_by_suffix(options.input.data, ".bmp");

        if(frames.length == 0)
        {
            frames = search_files_by_suffix(options.input.data, ".txt");
        }

        if(frames.length == 0)
        {
            printf("Can't find any file like .bmp or .txt in: %s\n", options.input.data);
            return 0;
        }

        args.frames = frames;

        sort_by_aplhabet(args.frames);

        args.framerate_ns = fps_ns(options.fps);
        
        args.color_pallete = options.color_pallete.data == NULL ? DEFAULT_CHAR_PALETTE : options.color_pallete.data;
        
        args.convert = 1;
        
        args.clear_console = options.clear_console;

        args.verbose = options.verbose;

        player(args);

        printf("\n");
    }

    return 0;
}