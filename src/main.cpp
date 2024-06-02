
#include <iostream>


int main() {
    int a = 7;
    int b = 2;
    float result = static_cast<float>(a)/b;
    std::cout << result << std::endl;
    std::cout << (int) 'A' << std::endl;
    std::cout << (char) 70 << std::endl;
    std::cout << static_cast <char> (65) << std::endl;
    return 0;
}