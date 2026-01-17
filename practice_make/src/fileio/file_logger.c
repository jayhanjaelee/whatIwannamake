#include "file_logger.h"
#include <stdio.h>

void write_input_to_file(const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Writing to %s. Press Ctrl+D (or Ctrl+Z) to stop:\n", filename);

    int input_ch;
    while ((input_ch = getchar()) != EOF) {
        fputc(input_ch, fp);
    }

    fclose(fp);
}
