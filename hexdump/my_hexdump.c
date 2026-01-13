#include <stdio.h>
#include <stdlib.h>

// TITLE: Coding Hexdump in C from Scratch
// URL: https://www.youtube.com/watch?v=mukG1kVJ1eY

void print_clear(char *s, int len) 
{
    printf("|");
    // 16 바이트 문자열로, null terminator 는 없지만 작동한다..
    // 1byte 씩 출력.
    for(int i=0; i<len; i++) 
    {
        if(s[i] < 0x20 || s[i] > 0x7e) 
        {
            // 특수문자는 . 로 치환하여 출력.
            printf(".");
        }
        else
        {
            // 실제 버퍼에 있는 문자열 출력.
            printf("%c", s[i]);
        }
    }
    printf("|");
}

int main(void) {
    int c;
    int mem_i = 0x0; // memory index
    char *s = (char *)calloc(0x10, sizeof(char));
    while((c = getchar()) != EOF) 
    {
        s[mem_i % 0x10] = c; // 0,1,2,3 ~ 15 로 인덱싱하기 위해 한 줄에 16바이트만 출력하기 때문에 16은 넘지 않음.
        // 2번째 비트 수가 바뀔때마다 메모리 주소 출력 ( start point of a row )
        if(mem_i % 0x10 == 0x0)
        {
            /*
           메모리 주소를 8자리 16진수로 보여주는 이유
           16진수 한자리수는 4비트임 (0 ~ 15)
           hexdump 의 메모리 주소 표현은 32비트 정수범위로 표현.
           32 비트 메모리 주소를 표현하기 위해서는 8자리가 필요.
            */
            printf("%08x ", mem_i); 
        }
        // 2x -> 0a 와 같이 두글자로 표현하기위해
        printf("%02x ", c);
        mem_i++;

        if(mem_i % 0x10 == 0x0)
        {
            print_clear(s, 0x10);
            printf("\n");
        }
    }

    // 마지막줄에 공백을 출력하는데 한줄당 3글자의 폭이 있고
    // 여백의 길이는 전체 바이트의 수 (0x10) - 현재 인덱스가 존재하는 바이트 위치 (0x10 % mem_i 를 계산해서 여백을 출력한다.
    printf("%*s", 3*(0x10 - (mem_i % 0x10)), " ");
    print_clear(s, mem_i % 0x10);
    printf("\n%08x", mem_i);
    printf("\n"); // sh 에서 줄바꿈 없이 프로그램이 종료되면 % 을 추가해서 줄바꿈 추가.

    return 0;
}
