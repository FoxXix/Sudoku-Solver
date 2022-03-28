#ifndef SOLVER_H_INCLUDE
#define SOLVER_H_INCLUDE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N {9};

bool isValidInRow(int grid[N][N], int& row_index, int& value);
bool isValidInCol(int grid[N][N], int& col_index, int& value);
bool isValidInBox(int grid[N][N], int row_start_index, int col_start_index, int& value);
bool isValidValue(int grid[N][N], int& row_index, int& col_index, int& value);
void printGrid(int grid[N][N]);

#endif // SOLVER_H_INCLUDE