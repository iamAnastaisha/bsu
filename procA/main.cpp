#include <iostream>

int main() {
    int num;
    std::cin >> num;
    for (int i = 0; i < 4; i++){
        std::cout << num + 4 << " ";
        std::cin >> num;
    }
    std::cout << num + 4 << "\n";
    return 0;
}
