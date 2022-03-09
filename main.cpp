#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N {9};

bool isValidInRow(int grid[N][N], int& row, int& value)
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
        if (grid[row][col_index] == value)
            return false;
    return true;
}

bool isValidInCol(int grid[N][N], int& col, int& value)
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
        if (grid[row_index][col] == value)
            return false;
    return true;
}

bool isValidInBox(int grid[N][N], int rowStartIndex, int colStartIndex, int& value)
{
    /**
     * Find if the given value is not found in the 3x3 'box' containing row:col.
     *
     * @param grid           Container of current grid state
     * @param rowStartIndex  Start index of row. Take 'rowIndex - (rowIndex % 3)'.
     * @param colStartIndex  Start index of col. Take 'colIndex - (colIndex % 3)'.
     * @param value          Value to check column with.
     * @return if value is able to be placed in the 3x3 'box' that row:col lives in.
     */

    for (int rowOffset = 0; rowOffset < 3; rowOffset++)
        for (int colOffset = 0; colOffset < 3; colOffset++)
            if (grid[rowStartIndex + rowOffset][colStartIndex + colOffset] == value)
                return false;

    return true;
}

bool isValidValue(int grid[N][N], int& row, int& col, int& value)
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

    return isValidInRow(grid, row, value) && isValidInCol(grid, col, value) && isValidInBox(grid, row - (row % 3), col - (col % 3), value);
}

void printGrid(int grid[N][N])
{
    /**
     * Pretty print out the grid for a user friendly visual.
     *
     * @param grid Container of current grid state
     * @return Null
     */

    for (int rowIndex = 0; rowIndex < N; rowIndex++)
    {
        if (rowIndex != 0 && rowIndex % 3 == 0)
        {
            // width of grid with N digits is (N*2+(4-1))
            // N digits, N spaces, -1 space at end, +4 spaces for block separators
            cout << string(N * 2 + 3, '-') << endl;
        }
        for (int colIndex = 0; colIndex < N; colIndex++)
        {
            if (colIndex != 0 && colIndex % 3 == 0)
                cout << "| ";
            cout << grid[rowIndex][colIndex] << ' ';
        }
        cout << endl;
    }
}

bool hasUnassigned(int grid[N][N], int& rowIndex, int& colIndex)
{
    /**
     * Function to find the next unassigned location in the grid.
     * A spot is unassigned when its value is 0. This function initializes
     * both the row and column index variables.
     *
     * @param grid     Container of current grid state.
     * @param rowIndex Row index.
     * @param colIndex Column index.
     * @return         bool; if solution at current state is found.
     */

    for (rowIndex = 0; rowIndex < N; rowIndex++) // loop through rows
        for (colIndex = 0; colIndex < N; colIndex++) // loop through columns
            if (grid[rowIndex][colIndex] == 0) // check if value is not set
                return true;

    return false;
}

bool solve(int grid[N][N])
{
    /**
     * Main function to find solutions to the given Sudoku grid.
     *
     * @param grid  Container of current grid state.
     * @return bool; if solution at current state is found.
     */

    int rowIndex;
    int colIndex;
    if (!hasUnassigned(grid, rowIndex, colIndex))
    {
        //printGrid(grid);
        return true;
    }
        

    for (int value = 1; value <= N; value++) // loop through possible values
    {
        if (isValidValue(grid, rowIndex, colIndex, value))
        {
            grid[rowIndex][colIndex] = value;
            //printGrid(grid);
            if (solve(grid))
                return true;
            grid[rowIndex][colIndex] = 0;   
        }
    }
    return false;
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
    printGrid(grid);
    cout << "Solving..." << endl;
    if (solve(grid))
        printGrid(grid);
    else
        cout << "No solution found!" << endl;

    return 0;
}