#include <string>
#include <iostream>

std::string fizzbuzz(uint32_t n) {
    std::string result = std::string(n % 3 == 0? "Fizz" : "") + (n % 5 == 0? "Buzz" : "");
    return result.empty() ? std::to_string(n) : result;
}

int main() {
    for(uint32_t i = 0; i < 100; i++) {
        std::cout << fizzbuzz(i) << std::endl;
    }
    return 0;
}