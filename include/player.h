#include "include/string-util.h"

typedef struct PLAYER_ARGS_S
{
    STRING_ARRAY frames; // OPTIONAL: if work with files
    uint32_t framerate_ns; // frame rate (fps) in nano seconds: 30fps = 1 000 000 / 30

    uint32_t* print_index;

    uint8_t dynamically_convert; // if the input is file: 0 for .txt, 1 for .bmp
    STRING_ARRAY files;
    STRING base_path; // where are the files dir

    char* color_palete;

    uint8_t* end;
} PLAYER_ARGS;

void player(PLAYER_ARGS);