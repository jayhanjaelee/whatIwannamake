/**
 * @file hj_time.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-17 21:22
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "hj_time.h"

const char* weekday_names[] = {
    "일",
    "월",
    "화",
    "수",
    "목",
    "금",
    "토"
};

// Hash Map 처럼 요일숫자값에 대응되는 문자열 구하기 위한 함수.
const char* get_weekday_name(Weekday day_num) {
    if (day_num >= SUNDAY && day_num <= SATURDAY) {
        return weekday_names[day_num];
    }
    return NULL;
}

// Function to get weekday number from name (hash map get, requires string comparison)
int get_weekday_number(const char* name) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(name, weekday_names[i]) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

int write_file(char *filename) {
    // open a file.
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr,
                "can't open %s: %s\n",
                filename,
                strerror(errno));
        return 1;
    }

    // write string into a file.
    int bytes_written = fprintf(fp, "Product Name: %s\n", "Lenovo Thinkpad X1 Carbon Gen 13");
    printf("%d bytes was written\n", bytes_written);

    // **important**: close file
    fclose(fp);

    return 0;
}

// 현재 날짜 출력
void print_current_date() {
    time_t now = time(NULL);         // Get current time
    struct tm *t = localtime(&now);  // Convert to local time structure

    int year = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day = t->tm_mday;
    Weekday weekday = t->tm_wday; // 0: sunday 6: satruday
    int hour = t->tm_hour;
    int min = t->tm_min;
    int sec = t->tm_sec;

    const char *weekday_name = get_weekday_name(weekday);

    // 2026-01-07 weekday 05:34:00
    fprintf(stdout, "%d-%d-%d (%s) %d:%d:%d\n",
            year, month, day, weekday_name, hour, min, sec);
}
