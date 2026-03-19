#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int id = 1;

typedef struct {
    int id;
    int price;
    char *name;
    char *url;
} Product;

typedef struct {
    Product *items;
    int count;
} ProductList;

// 상품 리스트에 상품 추가.
void add_item(ProductList *list, Product *new_item) {
    // 상품 리스트 추가하기 전에 Heap 메모리 사이즈 기존 사이즈보다 1 증가시켜주기.
    Product *temp = realloc(list->items, sizeof(Product) * (list->count + 1));
    // realloc 실패시 NULL 이 반환되므로 검증
    if (temp) {
        list->items = temp;
        list->items[list->count] = *new_item;
        list->count++;
    }
}

void print_product(Product *p) {
    printf("id: %d\n", p->id);
    printf("name: %s", p->name);
    printf("url: %s", p->url);
    printf("price: %d\n", p->price);
    printf("\n");
}

void print_products(ProductList *list) {
    for (int i=0; i<list->count; i++) {
        print_product(&list->items[i]);
    }
    printf("\n");
}

void print_menu() {
    printf("명령어를 입력하세요.\n");
    printf("1.조회\n");
    printf("2.추가\n");
    printf("3.삭제\n");
}

void print_add_menu() {
    printf("Enter name: ");
    printf("Enter url: ");
    printf("Enter price: ");
}

int my_atoi(char *str) {
    int result = 0;
    while (*str) {
        result += (result << 3) + (result << 1) + *str - '0';
        str++;
    }
    return result;
}

enum Menu { LIST = 1, ADD, DELETE };

int product_cnt = 0;

int main(int argc, char *argv[]) {
    ProductList *list = malloc(sizeof(ProductList));
    list->count = 0;

    while (1) {
        print_menu();

        int input;;
        scanf("%d", &input);
        getchar(); // \n 입력처리

        switch (input) {
            case LIST:
                print_products(list);
                break;
            case ADD: {
                Product *product = malloc(sizeof(Product));
                printf("Enter name: ");
                char *line = NULL;
                size_t linecapp;

                product->id = id++;
                getline(&line, &linecapp, stdin);
                product->name = strdup(line);

                printf("Enter url: ");
                getline(&line, &linecapp, stdin);
                product->url = strdup(line);

                printf("Enter price: ");
                getline(&line, &linecapp, stdin);
                product->price = atoi(strdup(line));

                add_item(list, product);
                print_product(product);
                printf("\n");

                break;
            }
            case DELETE:
                printf("DELETE\n");
                break;
        }
    }

    return 0;
}
