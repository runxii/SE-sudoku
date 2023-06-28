#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>
#include "testPuzzle.h"

using namespace std;

// 数独棋盘大小为9*9
const int SIZE = 9;

void print(const vector<vector<int>>& num)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << num[i][j] << " ";
        }
        cout << endl;
    }
}

bool IsRightPlace(vector<vector<int>>& num, int row, int col)
{
    int n = num[row][col];
    //注意i < row
    for (int i = 0; i < row; i++)
    {
        if (num[i][col] == n)
            return false;
    }
    //注意i < col
    for (int i = 0; i < col; i++)
    {
        if (num[row][i] == n)
            return false;
    }
    int row_start = row / 3;
    row_start *= 3;
    int row_end = row_start + 2;
    int col_start = col / 3;
    col_start *= 3;
    int col_end = col_start + 2;
    int i = row_start, j = col_start;
    //注意 k <= 8
    for (int k = 1; k <= 8; k++)
    {
        if (row != i || col != j)
        {
            if (num[i][j] == n)
                return false;
        }
        else
            break;
        if (j == col_end)
        {
            //注意j = col_start ！不要搞错换行时列的起始点！
            j = col_start;
            i = i + 1;
        }
        else
        {
            j = j + 1;
        }
    }
    return true;
}

bool generate_core(vector<vector<int>>& num, int row, int col)
{

    vector<int> number;
    for (int i = 1; i <= 9; i++)
        number.emplace_back(i);
    while (!number.empty())
    {
        int randindex = rand() % number.size();
        int randnum = number[randindex];
        number.erase(number.begin() + randindex);
        num[row][col] = randnum;
        if (IsRightPlace(num, row, col) == false)
            continue;
        if (row == SIZE - 1 && col == SIZE - 1)
        {
            return true;
        }
        int nextrow, nextcol;
        if (col == SIZE - 1)
        {
            nextrow = row + 1;
            nextcol = 0;
        }
        else
        {
            nextrow = row;
            nextcol = col + 1;
        }
        bool next = generate_core(num, nextrow, nextcol);
        if (next)
            return true;
    }
    if (number.empty())
    {
        num[row][col] = -5;
        return false;
    }
}

// 生成n个数独终局
void generateMultipleSudoku(int n) {
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < n; i++) {
        std::vector<std::vector<int>> num(SIZE, std::vector<int>(SIZE, -1));
        generate_core(num, 0, 0);

        std::cout << "Sudoku board " << (i + 1) << ":\n";
        print(num);
        std::cout << std::endl;
    }
}
