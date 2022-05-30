#include <iostream>
#include<cmath>

int main() {
    int num;
    std::cin >> num;
    for (int i = 0; i < 4; i++){
        std::cout << pow(num,3) << " ";
        std::cin >> num;
    }
    std::cout << pow(num,3) << "\n";
    return 0;
}
