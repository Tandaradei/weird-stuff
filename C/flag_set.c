#include <stdio.h>
#include <stdint.h>

typedef enum Values {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} Values;

#define FLAG_SET(NAME, FLAGS) \
typedef struct NAME { \
    union { \
        struct { \
            FLAGS \
        }; \
        uint8_t bytes[1]; \
    }; \
} NAME;


FLAG_SET(Test,
    uint8_t flag_a : 1;
    uint8_t flag_b : 1;
    uint8_t value : 2;
    uint8_t rest : 4;
    uint8_t flag_c : 1;
)

int main() {
    Test test = {
        .flag_a = 1,
        .flag_b = 0,
        .value = SOUTH,
        .flag_c = 1,
    };
    printf("sizeof Test: %llu\n", sizeof (Test));
    printf("test.flag_a: %d\n", test.flag_a);
    printf("test.flag_b: %d\n", test.flag_b);
    printf("test.value_c: %d\n", test.value);
    printf("test.flag_c: %d\n", test.flag_c);
    printf("All: \n");
    for(int i = 0; i < sizeof (Test); i++) {
        printf(" 0x%02x\n", test.bytes[i]);
    }
    return 0;
}