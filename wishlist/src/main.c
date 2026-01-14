#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char *name;
    char *url;
    int price;
} product_t;

typedef struct {
    product_t *items;
    int count;
} ProductList;

// 상품 리스트에 상품 추가.
void add_item(ProductList *list, product_t new_item) {
    // 상품 리스트 추가하기 전에 Heap 메모리 사이즈 기존 사이즈보다 1 증가시켜주기.
    product_t *temp = realloc(list->items, sizeof(product_t) * (list->count + 1));
    // realloc 실패시 NULL 이 반환되므로 검증
    if (temp) {
        list->items = temp;
        list->items[list->count] = new_item;
        list->count++;
    }
}

// 상품 목록 출력.
void print_product_list(ProductList *list) {
    // header
    printf("|%5s|%50s|%50s|%10s|\n", "id", "name", "url", "price");

    // body
    for (int i = 0; i < list->count; i++) {
        printf("|%05d|%50s|%50s|%10d|\n",
                list->items[i].id,
                list->items[i].name,
                list->items[i].url,
                list->items[i].price
                );
    }
    printf("\n");
}

void free_product_list(ProductList *list) {
    printf("%d count of product will be freed.\n", list->count);
    for (int i = 0; i < list->count; i++) {
        free(list->items[i]);
    }
}

int main(int argc, char *argv[]) {
    char input = '\0';
    ProductList p_list = {
        .items = NULL,
        .count = 0
    };

    printf("### MY WISHLIST Program. ###\n");

    while (1) {
        printf("\nEnter command (s: show, q: quit, i: init items): ");

        // 앞에 한 칸 띈 " %c"는 이전의 사용자가 입력한 엔터를 무시함. 이 처리를 안하면 입력버퍼가 리셋되지 않아서 출력문이 두번 실행됨.
        if (scanf(" %c", &input) != 1) continue;

        if (input == 'q') { // quit
            return 0;
        } 
        else if (input == 'i') { // init
            p_list.items = (product_t *)malloc(sizeof(product_t));
            product_t item = (product_t){
                .id = 1,
                .name = "APPLE WATCH STRAP (Black & Silver)",
                .url = "https://worthwhilemovement.com/product/p5-6-2",
                .price = 85000
            };
            add_item(&p_list, item);

            item = (product_t){
                .id = 2,
                .name = "Alpha 7 V - Full-frame Mirrorless Interchangeable Lens Camera",
                .url = "https://www.sony.co.kr/electronics/interchangeable-lens-cameras/ilce-7m5",
                .price = 3599000
            };
            add_item(&p_list, item);

            item = (product_t){
                .id = 3,
                .name = "ThinkPad X1 Carbon Gen 13",
                .url = "https://www.lenovo.com/kr/ko/p/laptops/thinkpad/thinkpadx1/thinkpad-x1-carbon-gen-13-aura-edition-14-inch-intel/21nxcto1wwkr4",
                .price = 327003
            };
            add_item(&p_list, item);
        }
        else if (input == 's') { // show
            print_product_list(&p_list);
        }

        free_product_list(&p_list);

        printf("\n");
    }

    return 0;
}
