#include <iostream>

int main() {
    int sum = 0;
    int num;
        std::cin >> num;
    for (int i = 0; i < 4; i++) {
        sum += num;
        std::cin >> num;
    }
    sum += num;
    std::cout << sum;
    return 0;
}
