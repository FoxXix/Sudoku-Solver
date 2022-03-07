#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define N 9

class SudokuSolver
{
    int grid[N][N];

    SudokuSolver(int grid_in[N][N])
    {
        grid = grid_in;
    }

    bool solve()
    {
        for (int row_index = 0; row_index < N; row_index++)
        {
            for (int col_index = 0; col_index < N; col_index++)
            {
                if (grid[row_index][col_index] != 0)
                {
                    for (int value = 1; value <= N; value++)
                    {
                        if (isValidValue(row_index, col_index, value))
                        {
                            grid[row_index][col_index] = value;
                            if (solve(grid))
                        }
                    }
                    return false; // no values found to be valid
                }
            }
        }
        return true; // no 0 values; solved!?
    }

    bool isEmpty(int row, int col)
    {
        return grid[row][col] == 0;
    }

    bool isValidValue(int row, int col, int value)
    {
        return (isValidInRow(row, col, value) && isValidInCol(row, col, value) && isValidInBox(row, col, value));
    }

    bool isValidInRow(int row, int col, int value)
    {
        for (int col_index = 0; col_index < N; col_index++)
        {
            if (grid[row][col_index] == value)
                return false;
        }
        return true;
    }

    bool isValidInCol(int row, int col, int value)
    {
        for (int row_index = 0; row_index < N; row_index++)
        {
            if (grid[row_index][col] == value)
                return false;
        }
        return true;
    }

    bool isValidInBox(int row, int col, int value)
    {
    }

    void printGrid()
    {
        for (int i = 0; i < N; i++)
        {
            if (i != 0 && i % (N / 3) == 0)
            {
                // width of grid with N digits is (N*2+(4-1))
                // N digits, N spaces, -1 space at end, +4 spaces for block separators
                cout << string(N * 2 + 3, '-') << endl;
            }
            for (int j = 0; j < N; j++)
            {
                if (j != 0 && j % (N / 3) == 0)
                {
                    cout << "| ";
                }
                cout << grid[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

int main()
{

    int grid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 3, 0, 8, 5},
                      {0, 0, 1, 0, 2, 0, 0, 0, 0},
                      {0, 0, 0, 5, 0, 7, 0, 0, 0},
                      {0, 0, 4, 0, 0, 0, 1, 0, 0},
                      {0, 9, 0, 0, 0, 0, 0, 0, 0},
                      {5, 0, 0, 0, 0, 0, 0, 7, 3},
                      {0, 0, 2, 0, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 4, 0, 0, 0, 9}};
    SudokuSolver sudoku = new SudokuSolver(grid);

    if (sudoku.solve(grid))
        sudoku.printGrid(grid);
    else
        cout << "No solution found!" << endl;

    return 0;
}