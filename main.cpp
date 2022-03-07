#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define N 9

bool isValidInRow(int grid[N][N], int row, int value)
{
    /**
     * Find if the given value at the specified row is not found.
     *
     * @param grid  Container of current grid state
     * @param row   Row index.
     * @param value Value to check row with.
     * @return if value is able to be placed in row index.
     */

    for (int col_index = 0; col_index < N; col_index++)
    {
        if (grid[row][col_index] == value)
            return false;
    }
    return true;
}

bool isValidInCol(int grid[N][N], int col, int value)
{
    /**
     * Find if the given value at the specified column is not found.
     *
     * @param grid  Container of current grid state
     * @param col   Column index.
     * @param value Value to check column with.
     * @return if value is able to be placed in column index.
     */

    for (int row_index = 0; row_index < N; row_index++)
    {
        if (grid[row_index][col] == value)
            return false;
    }
    return true;
}

bool isValidInBox(int grid[N][N], int row, int col, int value)
{
    /**
     * Find if the given value is not found in the 3x3 'box' containing row:col.
     *
     * @param grid  Container of current grid state
     * @param row   Row index.
     * @param col   Column index.
     * @param value Value to check column with.
     * @return if value is able to be placed in the 3x3 'box' that row:col lives in.
     */

    int rowLowLimit, rowHighLimit, colLowLimit, colHighLimit;

    if (row <= 2)
    {
        rowLowLimit = 0;
        rowHighLimit = 2;
    }
    else if (3 <= row <= 5)
    {
        rowLowLimit = 3;
        rowHighLimit = 5;
    }
    else if (row >= 6)
    {
        rowLowLimit = 6;
        rowHighLimit = 8;
    }

    if (col <= 2)
    {
        colLowLimit = 0;
        colHighLimit = 2;
    }
    else if (3 <= col <= 5)
    {
        colLowLimit = 3;
        colHighLimit = 5;
    }
    else if (col >= 6)
    {
        colLowLimit = 6;
        colHighLimit = 8;
    }

    for (int row_index = rowLowLimit; rowLowLimit <= rowHighLimit; row_index++)
    {
        for (int col_index = colLowLimit; colLowLimit <= colHighLimit; col_index++)
        {
            if (grid[row_index][col_index] == value)
                return false;
        }
    }

    return true;
}

void printGrid(int grid[N][N])
{
    /**
     * Pretty print out the grid for a user friendly visual.
     *
     * @param grid Container of current grid state
     * @return Null
     */

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

bool isValidValue(int grid[N][N], int row, int col, int value)
{
    /**
     * Wrapper function to find if value allowed in the specified location.
     * Valid if value is not found in the column, row or box.
     *
     * @param grid  Container of current grid state
     * @param row   Row index.
     * @param col   Column index.
     * @param value Value to check column with.
     * @return if value is allowed at row:col.
     */

    return (isValidInRow(grid, row, value) && isValidInCol(grid, col, value) && isValidInBox(grid, row, col, value));
}

bool solve(int grid[N][N])
{
    /**
     * Main function to find solutions to the given Sudoku grid.
     *
     * @param grid  Container of current grid state
     * @return bool; if solution at current state is found.
     */
    printGrid(grid);
    for (int row_index = 0; row_index < N; row_index++) // loop through rows
    {
        for (int col_index = 0; col_index < N; col_index++) // loop through columns
        {
            if (grid[row_index][col_index] != 0) // check if value is not set
            {
                for (int value = 1; value <= N; value++) // loop through possible values
                {
                    if (isValidValue(grid, row_index, col_index, value))
                    {
                        grid[row_index][col_index] = value;
                        return solve(grid);
                    }
                }
                return false; // no values found to be valid
            }
        }
    }
    return true; // no 0 values; solved!?
}

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
    if (solve(grid))
        printGrid(grid);
    else
        cout << "No solution found!" << endl;

    return 0;
}