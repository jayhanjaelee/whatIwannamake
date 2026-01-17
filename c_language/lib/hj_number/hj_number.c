/**
 * @file hj_number.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-17 23:18
 */

#include <time.h>
#include <stdlib.h>

#include "hj_number.h"

// 0 ~ n + 1 사이 숫자를 리턴
// TODO: random 숫자 생성이 이상함. 수정필요.
int randn(int n) {
    srand(time(NULL));   // Initialization, should only be called once.
    return rand() % (n + 1);
}
