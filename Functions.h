#pragma once
#include<iostream>
#include<fstream>
#include <mutex>
#include <thread>
#include<vector>

int Initialization(double**&, double**&, double**&);
void SetZero(double**&, int);
void Print(double**, int);
void MultiplyByElements(double**, double**, double**&, int);
void MultiplyBlocks(double**, double**, double**&, int, int, int, int, int);
void MultiplyByBlocks(double**, double**, double**&, int, int);