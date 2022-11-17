#include "include/fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#ifndef DT_REG
    #define DT_REG 8
#endif

int existDir(char* dir_path)
{
    DIR* dir_to_scan = opendir(dir_path);

    if (dir_to_scan == NULL)
    {
        return 0;
    }

    closedir(dir_to_scan);

    return 1;
}

STRING path_join(STRING path, STRING to_join)
{
    STRING toreturn;

    uint8_t has_split = endsWith(path.data, FOLDER_SPLIT);

    toreturn.length = path.length + to_join.length;

    if(!has_split)
    {
        //                 expect 1
        toreturn.length += strlen(FOLDER_SPLIT);
    }

    toreturn.data = (char*) malloc(toreturn.length + 1 * sizeof(char));

    //                                            + 1 for include '\0'
    strncpy(toreturn.data, path.data, path.length + 1);
    
    if (!has_split)
    {
        // expect copy {'/', '\0'} (2), in strncat use strlen(x) + 1 for '\0'
        strcat(toreturn.data, FOLDER_SPLIT);
    }
    
    //                                                  + 1 for include '\0'
    strncat(toreturn.data, to_join.data, to_join.length + 1);

    return toreturn;
}

STRING_ARRAY search_files_by_suffix(const char* dirpath, char* suffix)
{
    DIR* dir = opendir(dirpath);
    struct dirent *dfile;

    if(dir == NULL)
    {
        printf("Error opening folder: %s\n", dirpath);
        exit(0);
    }

    STRING_ARRAY files;
    files.length = 0;
    files.strings = (STRING*) malloc(files.length * sizeof(STRING));

    while ((dfile = readdir(dir)))
    {
        if (dfile->d_type == DT_REG)
        {
            if (endsWith(dfile->d_name, suffix))
            {
                STRING filename;
                filename.length = strlen(dfile->d_name);
                filename.data = (char*) malloc(filename.length * sizeof(char));

                strcpy(filename.data, dfile->d_name);

                files.strings = (STRING*) realloc(files.strings, (files.length + 1) * sizeof(STRING));

                files.strings[files.length++] = filename;
            }
        }
    }

    closedir(dir);

    return files;
}