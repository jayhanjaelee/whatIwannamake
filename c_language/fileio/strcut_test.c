#include <stdio.h>

struct Product {
    int id;
    char *name;
    struct Product *next;
};

int main(void) {
    // 1. 노드 초기화
    struct Product head_p = { 1, "apple watch strap", NULL };
    struct Product second_p = { 2, "bagpack", NULL };
    struct Product thrid_p = { 3, "Waviness blue jeans", NULL };

    // 2. 노드 연결
    head_p.next = &second_p;
    second_p.next = &thrid_p;

    // 3. 리스트 순회 (수정된 부분)
    // p를 '구조체'가 아닌 '구조체를 가리키는 포인터'로 선언합니다.
    for (struct Product *p = &head_p; p != NULL; p = p->next) {
        printf("id: %d, name: %s\n", p->id, p->name);
    }

    return 0;
}
