#include <iostream>

int main() {
    double a = 2.12345;
    int b{a};
    int c(a);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
}
