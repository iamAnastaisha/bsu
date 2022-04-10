#include"Functions.h"
#include<iomanip>
#include<chrono>

int main() {
  Initialization();

  auto start = std::chrono::high_resolution_clock::now();
  MultiplyByElements();
  auto end = std::chrono::high_resolution_clock::now();
  double time_taken =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  time_taken *= 1e-9;
  std::cout << "Usual algorithm: " << time_taken
            << std::setprecision(9) << "\n";
  Print(C);

  for (int i = 1; i <= n; i++) {
    int block_size = n / i;
    SetZero();
    start = std::chrono::high_resolution_clock::now();
    MultiplyByBlocks(block_size);
    end = std::chrono::high_resolution_clock::now();
    time_taken =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    std::cout << "Number of blocks: " << block_size * block_size
              << " Time: " << time_taken << std::setprecision(9) << "\n";
    Print(C);
  }
    pthread_exit(NULL);
}