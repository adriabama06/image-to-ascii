#include "include/string-util.h"

typedef struct PLAYER_ARGS_S
{
    // files or pre converted frames
    STRING_ARRAY frames;

    /*
    frame rate (fps) in nano seconds: 30fps = 1 000 000 / 30
    examples:
    1 000 000 / 60
    1 000 000 / 30
    1 000 000 / 25
    1 000 000 / 24
    1 001 000 / 24 => for animes
    */
    uint32_t framerate_ns;

    /*
    0 - the frames is preconverted ascii and is in the memory
    1 - the frames is input of files in dir
    */
    uint8_t convert;


    // (OPTIONAL) if the frames is list of files
    STRING base_path;


    /*
    example: ".-#"
    set DEFAULT_CHAR_PALETTE from "image.h" for default color palete
    */
    char* color_palete;

    // clear console before new line is printed, ONLY WORK ON LINUX!
    uint8_t clear_console;

    uint8_t verbose;
} PLAYER_ARGS;

#define fps_ns(fps) 1000000 / fps
#define cinema_fps_ns(fps) 1001000 / fps
void player(PLAYER_ARGS);