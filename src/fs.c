#include "include/util.h"

#include <stdlib.h>
#include <string.h>

#include <dirent.h>

int isDir(char *dir_path)
{
    DIR *dir_to_scan = opendir(dir_path);

    if (dir_to_scan == NULL)
    {
        return 0;
    }

    closedir(dir_to_scan);

    return 1;
}

STRING_ARRAY* search_bmp(const char *dir)
{
    DIR* bmp_dir = opendir(dir);
    uint32_t files_count = 0;

    while (readdir(bmp_dir)) { files_count++; }

    seekdir(bmp_dir, 0);

    struct dirent *dfile;

    STRING_ARRAY* strarr = (STRING_ARRAY*) malloc(sizeof(STRING_ARRAY));

    strarr->data = (char**) malloc(files_count * sizeof(char*));
    strarr->length = 0;

    for (uint32_t i = 0; i < files_count; i++)
    {
        dfile = readdir(bmp_dir);

        if (dfile->d_type == DT_REG)
        {
            if (endsWith(dfile->d_name, ".bmp"))
            {
                strarr->data[strarr->length] = (char*) malloc(strlen(dfile->d_name) * sizeof(char) + 1);

                strcpy(strarr->data[strarr->length], dfile->d_name);

                strarr->length++;
            }
        }
    }

    closedir(bmp_dir);

    return strarr;
}