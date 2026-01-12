#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char *name;
    char *url;
    int price;
} Product;

void print_product(Product* p) {
    printf("id:%d\n", p->id);
    printf("name:%s\n", p->name);
    printf("url:%s\n", p->url);
    printf("price:%d\n", p->price);
}

int main(int argc, char *argv[]) {
    printf("### MY WISHLIST Program. ###\n");

    char input = '\0';
    while (true) {
        printf("Manual\n");
        printf("s:show\tq: exit\n\n");
        printf("Enter command:");

        // 사용자가 입력한 개행이 입력 버퍼에 남아있게되어서 Enter command: 가 두번씩 호출되는 문제해결 -> " %c"
        scanf(" %c", &input);
        if (input == 'q') {
            return 0;
        } else if (input == 's') {
            Product *plist = (Product *)malloc(sizeof(Product));
            *plist = (Product){
                1,
                "APPLE WATCH STRAP (Black & Silver)",
                "https://worthwhilemovement.com/product/p5-6-2",
                85000
            };

            Product *tmp = (Product *)realloc(plist, sizeof(Product) * 2);
            *(plist+1) = (Product){
                2,
                "Alpha 7 V - Full-frame Mirrorless Interchangeable Lens Camera",
                "https://www.sony.co.kr/electronics/interchangeable-lens-cameras/ilce-7m5",
                3599000
            };

            tmp = (Product *)realloc(plist, sizeof(Product) * 3);
            *(plist+2) = (Product){
                3,
                "ThinkPad X1 Carbon Gen 13",
                "https://www.lenovo.com/kr/ko/p/laptops/thinkpad/thinkpadx1/thinkpad-x1-carbon-gen-13-aura-edition-14-inch-intel/21nxcto1wwkr4",
                2327003
            };

            print_product(plist);

            free(plist);
        }

        printf("\n");
    }

    return 0;
}
