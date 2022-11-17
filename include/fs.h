#include "include/string-util.h"

#ifdef _WIN32
    #define FOLDER_SPLIT "\\"
#else
    #define FOLDER_SPLIT "/"
#endif

int existDir(char*);

STRING path_join(STRING, STRING);

STRING_ARRAY search_files_by_suffix(const char*, char*);