#pragma once
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

int n;

class Params {
 public:
  double** matrix1;
  double** matrix2;
  double** matrix3;
  int row1;
  int row2;
  int column2;
  int block_size;

  Params(double** m1, double** m2, double** m3, int r1, int r2, int c2,
         int size) {
    matrix1 = m1;
    matrix2 = m2;
    matrix3 = m3;
    row1 = r1;
    row2 = r2;
    column2 = c2;
    block_size = size;
  }
};

void SetZero(double**& C, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = 0;
    }
  }
}

void Initialization(double**& A, double**& B, double**& C) {
  std::ifstream fin1("Matrix.txt");
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
}

void Print(double** m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << m[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void MultiplyByElements(double** A, double** B, double**& C) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
    }
}

void MultiplyBlocks(LPVOID params_) {
  auto* params = (Params*)params_;
  double** A = params->matrix1;
  double** B = params->matrix2;
  double** C = params->matrix3;
  int r1 = params->row1, r2 = params->row2, c2 = params->column2,
      block_size = params->block_size;
  for (int i = r1; i < r1 + block_size; i++) {
    for (int j = c2; j < c2 + block_size; j++) {
      double element = 0;
      for (int k = r2; k < r2 + block_size; k++) {
        element += A[i][k] * B[k][j];
      }
      HANDLE mtx = CreateMutex(NULL, TRUE, NULL);
      C[i][j] += element;
      ReleaseMutex(mtx);
    }
  }
}

void MultiplyByBlocks(double**& A, double**& B, double**& C, int block_size) {
  auto* handle = new HANDLE[pow(n, 3)];
  int count = 0;
  for (int i = 0; i < n; i += block_size)
    for (int j = 0; j < n; j += block_size) {
      for (int k = 0; k < n; k += block_size) {
        handle[count] = CreateThread(
            nullptr, 0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(&MultiplyBlocks),
            new Params(A, B, C, i, k, j, block_size), 0, nullptr);
        count++;
      }
    }
  WaitForMultipleObjects(n / block_size, handle, true, INFINITE);
}