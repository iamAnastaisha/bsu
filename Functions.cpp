#include"Functions.h"

int Initialization(double**& A, double**& B, double**& C) {
  std::ifstream fin1("Matrix1.txt");
  int n;
  fin1 >> n;
  A = new double*[n];
  B = new double*[n];
  C = new double*[n];
  for (int i = 0; i < n; i++) {
    A[i] = new double[n];
    B[i] = new double[n];
    C[i] = new double[n];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin1 >> A[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin1 >> B[i][j];
    }
  }
  SetZero(C, n);
  return n;
}

void SetZero(double**& C, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = 0;
    }
  }
}

void Print(double** m, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << m[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void MultiplyByElements(double** A, double** B, double**& C, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
    }
}

void MultiplyBlocks(double** A, double** B, double**& C, int r1, int r2, int c1,
                    int c2, int block_size) {
  std::mutex mtx;
  for (int i = r1; i < r1 + block_size; i++) {
    for (int j = c2; j < c2 + block_size; j++) {
      double element = 0;
      for (int k = 0; k < block_size; k++) {
        element += A[i][c1 + k] * B[r2 + k][j];
      }
     mtx.lock();
      C[i][j] += element;
     mtx.unlock();
    }
  }
}

void MultiplyByBlocks(double** A, double** B, double**& C, int block_size, int n) {
  std::vector<std::thread> threads;
  for (int i = 0; i < n; i += block_size)
    for (int j = 0; j < n; j += block_size) {
      for (int k = 0; k < n; k += block_size) {
        std::thread thr(MultiplyBlocks, std::ref(A), std::ref(B), std::ref(C), i, k, k, j, block_size);
        threads.push_back(std::move(thr));
      }
    }
  for (std::thread& thread : threads) {
    thread.join();
  }
}