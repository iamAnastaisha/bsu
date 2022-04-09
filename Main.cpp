#include <chrono>
#include <iomanip>
#include "Functions.h"

int main() {
  double** m1;
  double** m2;
  double** m3;
  Initialization(m1, m2, m3);

  auto start = std::chrono::high_resolution_clock::now();
  MultiplyByElements(m1, m2, m3);
  auto end = std::chrono::high_resolution_clock::now();
  double time_taken =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  time_taken *= 1e-9;
  std::cout << "Usual algorithm: " << time_taken << std::setprecision(9)
            << "\n";
  Print(m3);

  for (int i = 1; i <= n; i++) {
    int block_size = n / i;
    SetZero(m3, n);
    start = std::chrono::high_resolution_clock::now();
    MultiplyByBlocks(m1, m2, m3, block_size);
    end = std::chrono::high_resolution_clock::now();
    time_taken =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    time_taken *= 1e-9;
    std::cout << "Number of blocks: " << block_size * block_size
              << " Time: " << time_taken << std::setprecision(9) << "\n";
    Print(m3);
  }
  return 0;
}