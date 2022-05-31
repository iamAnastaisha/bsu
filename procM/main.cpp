#include <iostream>

int main() {
    int num;
    for (int i = 0; i < 5; i++){
        std::cin >> num;
        std::cout << num * 7;
        if (i==4) std::cout << "\n";
        else std::cout << " ";
    }
    return 0;
}
