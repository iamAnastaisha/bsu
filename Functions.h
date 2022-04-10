//
// Created by anastasiya on 9.04.22.
//

#ifndef MATR_LINUX_FUNCTIONS_H
#define MATR_LINUX_FUNCTIONS_H

#include<iostream>
#include<fstream>
#include <pthread.h>
#include<cmath>

int n;
double** A;
double** B;
double** C;
pthread_mutex_t mtx;

struct Params{
    int row1;
    int row2;
    int column2;
    int block_size;

    Params(int r1, int r2, int c2, int bl_size){
        row1 = r1;
        row2 = r2;
        column2 = c2;
        block_size = bl_size;
    }
};

void SetZero() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }
}

void Initialization() {
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
    SetZero();
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

void MultiplyByElements() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
        }
}

void *MultiplyBlocks(void* params_) {
    auto* params = (Params*) params_;
    int r1 = params->row1,  r2 = params->row2,
     c2 = params->column2,  block_size = params->block_size;
    for (int i = r1; i < r1 + block_size; i++) {
        for (int j = c2; j < c2 + block_size; j++) {
            double element = 0;
            for (int k =r2; k < r2 + block_size; k++) {
                element += A[i][k] * B[k][j];
            }
            pthread_mutex_lock(&mtx);
            C[i][j] += element;
            pthread_mutex_unlock(&mtx);
        }
    }
    return nullptr;
}

void MultiplyByBlocks(int block_size) {
    int size = pow(n, 3);
    auto* threads = new pthread_t[size];
    int count = 0;
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                pthread_mutex_init(&mtx, 0);
                pthread_create(&threads[count], NULL, MultiplyBlocks, (void*) new Params(i,j,k,block_size));
                count++;
                pthread_mutex_destroy(&mtx);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], nullptr);
   }
}

#endif //MATR_LINUX_FUNCTIONS_H
