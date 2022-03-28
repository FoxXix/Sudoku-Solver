#ifndef GENERATOR_H_INCLUDE
#define GENERATOR_H_INCLUDE

#include "solver.h"

class SudokuGenerator
{
private:
    int K;
public:
    SudokuGenerator(int k);
    void fillValues();
    void fillDiagonal();
    bool fillEmpty(int row_index, int col_index);
    void removeKDigits();
    void fillBox(int& row_start_index, int& col_start_index);
    int grid[N][N];
};

#endif // GENERATOR_H_INCLUDE