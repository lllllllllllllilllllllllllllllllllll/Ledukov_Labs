#include "Libr.h"

const char *read_filename(const char * filename) {
    printf(filename);
    char* fn=( char*)calloc(1, sizeof( char)*1001);
    scanf("%1000s", fn);
    return fn;
}


