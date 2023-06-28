#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include "puzzle.h"


// 检查数独规则
bool isSafe(Cell board[][SIZE], int row, int col, int num) {
    // 检查同一行是否存在重复数字
    for (int c = 0; c < SIZE; ++c) {
        if (board[row][c].value == num) {
            return false;
        }
    }

    // 检查同一列是否存在重复数字
    for (int r = 0; r < SIZE; ++r) {
        if (board[r][col].value == num) {
            return false;
        }
    }

    // 检查同一3x3方格是否存在重复数字
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[startRow + r][startCol + c].value == num) {
                return false;
            }
        }
    }

    return true;
}


// 查找未分配的单元格
bool findUnassignedCell(Cell board[][SIZE], int& row, int& col) {
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (board[row][col].value == 0) {
                return true;
            }
        }
    }
    return false;
}

// 生成完整的数独棋盘
bool generateBoard(Cell board[][SIZE]) {
    int row, col;

    if (!findUnassignedCell(board, row, col)) {
        // 如果所有单元格都已分配，表示问题已解决
        return true;
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(board, row, col, num)) {
            // 尝试分配数字
            board[row][col].value = num;

            if (generateBoard(board)) {
                // 递归解决剩余的数独问题
                return true;
            }

            // 如果分配的数字导致后续无解，则回溯
            board[row][col].value = 0;
        }
    }

    return false;
}

// 测试 generateBoard 函数
void testGenerateBoard() {
    Cell test[9][9];
    

    // 调用 generateBoard 函数
    generateBoard(test);

    // 检查生成的数独游戏是否满足规则

    // 检查每行是否满足唯一性
    for (int i = 0; i < 9; i++) {
        int count[10] = { 0 }; // 记录数字出现的次数
        for (int j = 0; j < 9; j++) {
            int num = test[i][j].value;
            assert(num >= 1 && num <= 9); // 数字应在有效范围内
            count[num]++;
            assert(count[num] == 1); // 数字在当前行中只能出现一次
        }
    }

    // 检查每列是否满足唯一性
    for (int j = 0; j < 9; j++) {
        int count[10] = { 0 }; // 记录数字出现的次数
        for (int i = 0; i < 9; i++) {
            int num = test[i][j].value;
            assert(num >= 1 && num <= 9); // 数字应在有效范围内
            count[num]++;
            assert(count[num] == 1); // 数字在当前列中只能出现一次
        }
    }

    // 检查每个小九宫格是否满足唯一性
    for (int blockRow = 0; blockRow < 3; blockRow++) {
        for (int blockCol = 0; blockCol < 3; blockCol++) {
            int count[10] = { 0 }; // 记录数字出现的次数
            for (int i = blockRow * 3; i < blockRow * 3 + 3; i++) {
                for (int j = blockCol * 3; j < blockCol * 3 + 3; j++) {
                    int num = test[i][j].value;
                    assert(num >= 1 && num <= 9); // 数字应在有效范围内
                    count[num]++;
                    assert(count[num] == 1); // 数字在当前小九宫格中只能出现一次
                }
            }
        }
    }

    std::cout << "generateBoard function passed the test.\n";
}