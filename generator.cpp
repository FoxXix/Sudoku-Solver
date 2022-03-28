#include "generator.h"

SudokuGenerator::SudokuGenerator(int k)
{
    for (int col_index = 0; col_index < N; col_index++)
    {
        for (int row_index = 0; row_index < N; row_index++)
            grid[col_index][row_index] = 0;
    }

    // update the seed for the rand function - allows different results each run
    srand (time(NULL));
    K = k;
    fillValues();
}

void SudokuGenerator::fillValues()
{
    fillDiagonal();
    fillEmpty(0, N);
    removeKDigits();
}

void SudokuGenerator::fillDiagonal()
{
    for (int row_index = 0; row_index < N; row_index = row_index + 3)
        fillBox(row_index, row_index);
}

bool SudokuGenerator::fillEmpty(int row_index, int col_index)
{
    if (col_index >= N && row_index < N-1)
    {
        row_index++;
        col_index = 0;
    }
    if (row_index >= N && col_index >= N)
        return true;

    if (row_index < 3)
    {
        if (col_index < 3)
            col_index = 3;
    }
    else if (row_index < N-3)
    {
        if (col_index == (int)(row_index/3)*3)
            col_index = col_index + 3;
    }
    else
    {
        if (col_index == N-3)
        {
            row_index++;
            col_index=0;
            if (row_index >= N)
                return true;
        }
    }
    for (int value = 1; value<=N; value++)
    {
        if (isValidValue(grid, row_index, col_index, value))
        {
            grid[row_index][col_index] = value;
            if (fillEmpty(row_index, col_index+1))
                return true;

            grid[row_index][col_index] = 0;
        }
    }
    return false;
}

void SudokuGenerator::removeKDigits()
{
    int count = K;
    while (count != 0)
    {
        int cell_id = rand() % (N*N) - 1;
        int row_index = cell_id / N;
        int col_index = cell_id % N - 1;

        if (grid[row_index][col_index] != 0)
        {
            count--;
            grid[row_index][col_index] = 0;
        }
    }
}

void SudokuGenerator::fillBox(int& row_start_index, int& col_start_index)
{
    int value;

    for (int row_index = 0; row_index < 3; row_index++)
    {
        for (int col_index = 0; col_index < 3; col_index++)
        {
            do
            {
                value = rand() % N + 1;
            } while (!isValidInBox(grid, row_start_index, col_start_index, value));
            
            grid[row_start_index + row_index][col_start_index + col_index] = value;
        }
    }
}
