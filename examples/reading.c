
#include <stdio.h>

#include "microtar.h"

int main() {
    mtar_t tar;
    mtar_header_t h;
    char *p;

    /* Open archive for reading */
    int open_err = mtar_open(&tar, "test.tar", "r");
    if ( open_err != MTAR_ESUCCESS ) {
        fprintf_s(stderr, "Could not open test.tar for reading: %d \n", open_err);
        return 1;
    }

    /* Print all file names and sizes */
    while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
        printf("%s (%d bytes)\n", h.name, h.size);
        mtar_next(&tar);
    }

    /* Load and print contents of file "test.txt" */
    mtar_find(&tar, "test.txt", &h);
    p = calloc(1, h.size + 1);
    mtar_read_data(&tar, p, h.size);
    printf("%s", p);
    free(p);

    /* Close archive */
    mtar_close(&tar);

    return 0;
}
