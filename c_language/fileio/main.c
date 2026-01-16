#include <stdio.h>
#include <string.h>

int my_getline(char *line, int max) {
    if (fgets(line, max, stdin) != NULL) {
        return 0;
    } else {
        return strlen(line);
    }
}

int main(int argc, char *argv[]) {
    char *str = "Hello, World\n";

    int line = my_getline(str, 1);
    printf("line:%d\n", line);

    return 0;
}
