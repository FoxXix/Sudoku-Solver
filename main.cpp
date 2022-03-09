#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N {9};

bool isValidInRow(int grid[N][N], int& row_index, int& value)
{
    /**
     * Find if the given value at the specified row is not found.
     *
     * @param grid      Container of current grid state
     * @param row_index Row index.
     * @param value     Value to check row with.
     * @return          bool; if value is able to be placed in row index.
     */

    for (int col_index = 0; col_index < N; col_index++)
        if (grid[row_index][col_index] == value)
            return false;
    return true;
}

bool isValidInCol(int grid[N][N], int& col_index, int& value)
{
    /**
     * Find if the given value at the specified column is not found.
     *
     * @param grid      Container of current grid state
     * @param col_index Column index.
     * @param value     Value to check column with.
     * @return          bool; if value is able to be placed in column index.
     */

    for (int row_index = 0; row_index < N; row_index++)
        if (grid[row_index][col_index] == value)
            return false;
    return true;
}

bool isValidInBox(int grid[N][N], int row_start_index, int col_start_index, int& value)
{
    /**
     * Find if the given value is not found in the 3x3 'box' containing row:col.
     *
     * @param grid            Container of current grid state
     * @param row_start_index Start index of row. Take 'row_index - (row_index % 3)'.
     * @param col_start_index Start index of col. Take 'col_index - (col_index % 3)'.
     * @param value           Value to check column with.
     * @return                bool; if value is able to be placed in the 3x3 'box' that row:col lives in.
     */

    for (int row_offset = 0; row_offset < 3; row_offset++)
        for (int col_offset = 0; col_offset < 3; col_offset++)
            if (grid[row_start_index + row_offset][col_start_index + col_offset] == value)
                return false;

    return true;
}

bool isValidValue(int grid[N][N], int& row_index, int& col_index, int& value)
{
    /**
     * Wrapper function to find if value allowed in the specified location.
     * Valid if value is not found in the column, row or box.
     *
     * @param grid      Container of current grid state
     * @param row_index Row index.
     * @param col_index Column index.
     * @param value     Value to check column with.
     * @return          bool; if value is allowed at row:col.
     */

    return isValidInRow(grid, row_index, value) && 
           isValidInCol(grid, col_index, value) && 
           isValidInBox(grid, row_index - (row_index % 3), col_index - (col_index % 3), value);
}

void printGrid(int grid[N][N])
{
    /**
     * Pretty print out the grid for a user friendly visual.
     *
     * @param grid Container of current grid state
     * @return     Null
     */

    for (int row_index = 0; row_index < N; row_index++)
    {
        if (row_index != 0 && row_index % 3 == 0)
        {
            // width of grid with N digits is (N*2+(4-1))
            // N digits, N spaces, -1 space at end, +4 spaces for block separators
            cout << string(N * 2 + 3, '-') << '\n';
        }
        for (int col_index = 0; col_index < N; col_index++)
        {
            if (col_index != 0 && col_index % 3 == 0)
                cout << "| ";
            cout << grid[row_index][col_index] << ' ';
        }
        cout << '\n';
    }
    cout << "\n\n";
}

bool hasUnassigned(int grid[N][N], int& row_index, int& col_index)
{
    /**
     * Function to find the next unassigned location in the grid.
     * A spot is unassigned when its value is 0. This function initializes
     * both the row and column index variables.
     *
     * @param grid      Container of current grid state.
     * @param row_index Row index.
     * @param col_index Column index.
     * @return          bool; if solution at current state is found.
     */

    for (row_index = 0; row_index < N; row_index++)
        for (col_index = 0; col_index < N; col_index++)
            if (grid[row_index][col_index] == 0)
                return true;

    return false;
}

bool solve(int grid[N][N])
{
    /**
     * Main function to find solutions to the given Sudoku grid.
     * Designed to be a recursive function and backtrack when no valid
     * values are found for a given Sudoku configuration.
     *
     * @param grid  Container of current grid state.
     * @return      bool; if solution at current state is found.
     */

    int row_index;
    int col_index;
    if (!hasUnassigned(grid, row_index, col_index))
        return true; // base case: all spots assigned values, solved! 

    for (int value = 1; value <= N; value++)
    {
        if (isValidValue(grid, row_index, col_index, value))
        {
            grid[row_index][col_index] = value;
            // recursively call solve to fill in all the unassigned spots
            if (solve(grid))
                return true;
            
            // backtracking; reset the value and try again with other values
            grid[row_index][col_index] = 0;   
        }
    }
    // no valid values were found in this run
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
    // int grid[N][N] = { { 0, 9, 0, 0, 0, 0, 8, 5, 3 },
    //                     { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
    //                     { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
    //                     { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
    //                     { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    //                     { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
    //                     { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
    //                     { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
    //                     { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };
    printGrid(grid);
    cout << "Solving...\n\n";
    if (solve(grid))
        printGrid(grid);
    else
        cout << "No solution found!\n\n";

    return 0;
}