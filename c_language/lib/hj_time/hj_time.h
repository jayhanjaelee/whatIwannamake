/**
 * @file hj_time.h
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-17 21:23
 */

#ifndef HJ_TIME_H
#define HJ_TIME_H

typedef enum {
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Weekday;

const char* get_weekday_name(Weekday day_num);
int get_weekday_number(const char* name);
int write_file(char *filename);
void print_current_date();

#endif /* HJ_TIME_H */

