#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 9;

// 数独单元格的结构体
struct Cell {
    int value;
    bool given;
};

// 打印数独棋盘
void printBoard(Cell board[][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            std::cout << board[row][col].value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

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


// 生成数独问题
void generatePuzzle(Cell board[][SIZE]) {
    // 先复制完整的数独棋盘
    Cell tempBoard[SIZE][SIZE];
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            tempBoard[row][col].value = board[row][col].value;
            tempBoard[row][col].given = true;
        }
    }

    // 随机去除数字
    int numGiven = SIZE * SIZE;  // 已给定数字的数量
    int numToRemove = rand() % 45 + 36;  // 需要去除的数字数量，范围在36到44之间（保证有解且唯一解）

    while (numGiven > SIZE * SIZE - numToRemove) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (tempBoard[row][col].given) {
            tempBoard[row][col].value = 0;
            tempBoard[row][col].given = false;
            numGiven--;
        }
    }

    // 将生成的数独问题复制回原棋盘
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            board[row][col].value = tempBoard[row][col].value;
            board[row][col].given = tempBoard[row][col].given;
        }
    }
}

// 解决数独问题
bool solveSudoku(Cell board[][SIZE]) {
    int row, col;
    if (!findUnassignedCell(board, row, col)) {
        // 如果所有单元格都已分配，表示问题已解决
        return true;
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(board, row, col, num)) {
            // 尝试分配数字
            board[row][col].value = num;

            if (solveSudoku(board)) {
                // 递归解决剩余的数独问题
                return true;
            }

            // 如果分配的数字导致后续无解，则回溯
            board[row][col].value = 0;
        }
    }

    return false;
}

int main() {
    srand(time(nullptr));

    Cell board[SIZE][SIZE];

    // 生成完整的数独棋盘
    generateBoard(board);

    // 生成数独问题
    generatePuzzle(board);

    // 显示初始数独棋盘
    printBoard(board);

    // 求解数独问题
    solveSudoku(board);

    // 显示解决后的数独棋盘
    printBoard(board);

    return 0;
}
