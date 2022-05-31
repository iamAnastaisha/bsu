#include <iostream>

int main() {
    int sum = 0;
    int num;
    for (int i = 0; i < 5; i++) {
        std::cin >> num;
        sum += num;
    }
    std::cout << sum;
    return 0;
}
