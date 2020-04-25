/*
Inspired by https://maxliani.wordpress.com/2020/04/23/dev-its-all-about-memory-part-3/
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
To provide a "meaningful" purpose for a value with more than 2 options
*/
typedef enum Direction {
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST
} Direction;

#define FLAG_SET(NAME, FLAGS) \
typedef struct NAME { \
    union { \
        struct { \
            FLAGS \
        }; \
        uint8_t bytes[1]; /* using array of size 1 here, so we can access all bytes easily as an array */ \
    }; \
} NAME;


/*
'type name : n' sets the bit requirement for data segment 'name' where 'n' is the # of bits
# of bits per data segment must be <= # of bits used by 'type' (e.g. <= 8 for uint8_t)
*/
FLAG_SET(Test,
    uint8_t flag_a : 1; 
    uint8_t flag_b : 1;
    uint8_t dir : 2;
    uint8_t padding : 4; // just here for testing, so that we get 2 bytes as total size
    uint8_t flag_c : 1;
)

static const Test my_config = {
    .dir = DIR_SOUTH,
    .flag_c = true
};

bool test_equal(const uint8_t bytes_a[], const uint8_t bytes_b[], size_t size) {
    for(size_t i = 0; i < size; i++) {
        if(bytes_a[i] != bytes_b[i]) {
            return false;
        }
    }
    return true;
}

bool test_subset(const uint8_t bytes_a[], const uint8_t bytes_subset[], size_t size) {
    for(size_t i = 0; i < size; i++) {
        if((bytes_a[i] & bytes_subset[i]) != bytes_subset[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    Test test = {
        .flag_a = true,
        .dir = DIR_SOUTH,
        .flag_c = true,
    };
    printf("sizeof Test: %llu\n", sizeof (Test));
    printf("flag_a: %d\n", test.flag_a);
    printf("flag_b: %d\n", test.flag_b);
    printf("dir: %d\n", test.dir);
    printf("flag_c: %d\n", test.flag_c);
    printf("Bytes: \n");
    for(int i = 0; i < sizeof (Test); i++) {
        printf(" 0x%02x\n", test.bytes[i]);
    }

    // printout
    /*
    sizeof Test: 2
    flag_a: 1
    flag_b: 0
    value_c: 2
    flag_c: 1
    Bytes:
     0x09
     0x01
    */

    // Easier flag test than "oldschool" flagset && flag
    if(test.flag_a) {
        printf("flag_a is set\n");
    }
    printf("flag_b is%s set\n", test.flag_b ? "" : " not");
    // printout
    /*
    flag_a is set
    flag_b is not set
    */

    // Test against flag set
    // Excatly the same
    if(test_equal(test.bytes, my_config.bytes, sizeof (Test))) {
        printf("test is exactly the same as my_config\n");
    }
    // subset test
    if(test_subset(test.bytes, my_config.bytes, sizeof (Test))) {
        printf("test has atleast all the props of my_config");
    }
    // printout
    /*
    test has atleast all the props of my_config
    */
    return 0;
}