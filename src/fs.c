#include <stdlib.h>
#include <string.h>

#include <dirent.h>

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