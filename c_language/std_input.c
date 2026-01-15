#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// 소문자라면
bool is_lowercase(int ch) {
    return ch >= 97 && ch <= 122;
}

// 대문자라면
bool is_uppercase(int ch) {
    return ch >= 65 && ch <= 90;
}

int my_tolower(int ch) {
    if (is_uppercase(ch)) {
        return ch += 32;
    }

    return ch;
}

int my_toupper(int ch) {
    if (is_lowercase(ch)) {
        return ch -= 32;
    }

    return ch;
}

int main(int argc, char *argv[]) {
    char ch;
    while ((ch = getchar()) != EOF) {
        if (is_lowercase(ch)) {
            putchar(my_toupper(ch));
        }
        else if (is_uppercase(ch)) {
            putchar(my_tolower(ch));
        }
    }
    return 0;
}
