#include "generator.h"

SudokuGenerator::SudokuGenerator(int k)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;
    }
    K = k;
    fillValues();
}

SudokuGenerator::~SudokuGenerator()
{
    for (int i = 0; i < N; i++)
    {
        delete grid[i];
    }
    delete grid;
}

void SudokuGenerator::fillValues()
{
    fillDiagonal();
    fillEmpty(0, N);
    removeKDigits();
}

void SudokuGenerator::fillDiagonal()
{
    for (int i = 0; i < N; i=i+3)
        fillBox(i, i);
}

bool SudokuGenerator::fillEmpty(int i, int j)
{
    if (j >= N && i < N-1)
    {
        i++;
        j = 0;
    }
    if (i >= N && j >= N)
        return true;

    if (i < 3)
    {
        if (j < 3)
            j = 3;
    }
    else if (i < N-3)
    {
        if (j == (int)(i/3)*3)
            j = j + 3;
    }
    else
    {
        if (j == N-3)
        {
            i++;
            j=0;
            if (i >= N)
                return true;
        }
    }
    for (int value = 1; value<=N; value++)
    {
        if (isValidValue(grid, i, j, value))
        {
            grid[i][j] = value;
            if (fillEmpty(i, j+1))
                return true;

            grid[i][j] = 0;
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
        // extract coordinates i  and j
        int i = (cell_id / N);
        int j = cell_id % 9;
        if (j != 0)
            j = j - 1;

        if (grid[i][j] != 0)
        {
            count--;
            grid[i][j] = 0;
        }
    }
}

void SudokuGenerator::fillBox(int& row_start_index, int& col_start_index)
{
    int value;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
            {
                value = rand() % 9 + 1;
            } while (!isValidInBox(grid, row_start_index, col_start_index, value));
            
            grid[row_start_index + i][col_start_index + j] = value;
        }
    }
}
