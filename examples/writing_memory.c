
#include <string.h>

#include "microtar.h"

int main() {
    mtar_t tar;
    mtar_mem_stream_t mem;
    char buffer[4096];
    const char *str1 = "Hello world";
    const char *str2 = "Goodbye world";

    /* Initialize memory stream object */
    mtar_init_mem_stream(&mem, buffer, sizeof(buffer));
    /* Open archive for writing */
    mtar_open_mem(&tar, &mem);

    /* Write strings to files `test1.txt` and `test2.txt` */
    mtar_write_file_header(&tar, "test1.txt", strlen(str1));
    mtar_write_data(&tar, str1, strlen(str1));
    mtar_write_file_header(&tar, "test2.txt", strlen(str2));
    mtar_write_data(&tar, str2, strlen(str2));

    /* Finalize -- this needs to be the last thing done before closing */
    mtar_finalize(&tar);

    /* Close archive */
    mtar_close(&tar);

    /* Now you can process the buffer */
    size_t data_len = mem.pos;
    FILE *fp = fopen("test.tar", "wb");
    fwrite(buffer, data_len, 1, fp);
    fclose(fp);

    return 0;
}
