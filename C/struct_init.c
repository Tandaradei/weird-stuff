#include <stdio.h>
#include <stdint.h>

typedef struct MyStructure {
    uint32_t x;
    struct {
        float width;
        float height;
    } size;
} MyStructure;

void printStructure(const MyStructure* my_struct) {
    printf("x: %d\n", my_struct->x);
    printf("size.width: %f\n", my_struct->size.width);
    printf("size.height: %f\n", my_struct->size.height);
}

int main() {
    MyStructure my_structure;
    printStructure(&(MyStructure){.size.height = 0.0f});
    MyStructure my_structure2 = {5, {3.0f, 4.0f}};
    printStructure(&(MyStructure){5, 3.0f, 4.0f});
    MyStructure my_structure3 = {5};
    printStructure(&my_structure3);
    MyStructure my_structure4 = {.size = {.width = 2.0f}};
    printStructure(&my_structure4);

    return 0;
}