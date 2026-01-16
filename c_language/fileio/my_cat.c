#include <stdio.h>
#include <stdlib.h>

// stdout 에 출력하는 방법
void print_to_stdout() {
    int ch;

    while ((ch = getc(stdin)) != EOF) {
        putc(ch, stdout);
    }
}

int write_file_ex1() {
    int data[] = {10, 20, 30, 40, 50};
    size_t num_elements = sizeof(data) / sizeof(data[0]);
    FILE *file_ptr;
    size_t elements_written;

    // 1. Open file in binary write mode and check for NULL
    // file_ptr = fopen("output.bin", "wb");
    file_ptr = fopen("output.txt", "w");
    if (file_ptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // 2. Write data and check the return value
    elements_written = fwrite(data, sizeof(int), num_elements, file_ptr);
    if (elements_written < num_elements) {
        fprintf(stderr, "Warning: only %zu of %zu elements written successfully\n", elements_written, num_elements);
        // Additional error handling can go here, e.g. checking ferror() after a partial write
    } else {
        printf("Successfully wrote %zu elements to file\n", elements_written);
    }

    // 3. Close the file to flush buffers and free resources
    if (fclose(file_ptr) != 0) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // std input -> getc()
    // std output -> putc()

    /**
      getc, putc 란 뭘까.
      결국 character 를 입출력하는 것.
      둘 다 파일 스트림을 argument (인자) 로 받는다.
      getc 는 첫번째 인자로 파일 스트림을 전달해주면 되고,
      putc 는 첫번째 인자로 출력하고 싶은 character, 두번째 인자로 파일스트림 (어디로 출력할지, 파일이 될수도 있고 standard output 이 될수도 있고)
      */

    // print_to_stdout();

    write_file_ex1();

    return 0;
}
