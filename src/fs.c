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

char* get_filename(char* file)
{
    // myfile.txt
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    // myfile.txt
    //       |<-- return pointer to this word
    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return NULL;
    }

    *ext = '\0';

    /*
        Ignore this if you not are adriabama06
        TOME:
            if i like, copy the filename to filename_clear because "txt" exist in memory but because is "\0" where "." whas before it uses extra memory
    */

    return filename;
}

char* get_extension(char* file)
{
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return NULL;
    }

    /*
        Ignore this if you not are adriabama06
        TOME:
            SEE get_filename
            ext_clear = malloc strlen(ext)
            copy ext -> ext_clear
            free ext
            return ext_clear
    */

    return ext;
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
                files.strings = (STRING*) realloc(files.strings, (files.length + 1) * sizeof(STRING));

                files.strings[files.length++] = string_from(dfile->d_name);
            }
        }
    }

    closedir(dir);

    return files;
}