#include <iostream>

int main() {
    int sum = 0;
    int num;
<<<<<<< HEAD
    for (int i = 0; i < 5; i++) {
=======
        std::cin >> num;
    for (int i = 0; i < 4; i++) {
        sum += num;
>>>>>>> lab7_lin
        std::cin >> num;
        sum += num;
    }
    std::cout << sum;
    return 0;
}
