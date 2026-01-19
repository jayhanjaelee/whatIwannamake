#include <stdio.h>

struct Human {
    char *name;
    int age;
};

int main(void) {

    struct Human hanjae;

    printf("%zu\n", sizeof(hanjae));
    printf("%zu\n", sizeof(hanjae.name));
    printf("%zu\n", sizeof(hanjae.age));

    return 0;
}
