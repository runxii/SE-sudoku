#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 9;

// ������Ԫ��Ľṹ��
struct Cell {
    int value;
    bool given;
};

// ��ӡ��������
void printBoard(Cell board[][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            std::cout << board[row][col].value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// �����������
bool isSafe(Cell board[][SIZE], int row, int col, int num) {
    // ���ͬһ���Ƿ�����ظ�����
    for (int c = 0; c < SIZE; ++c) {
        if (board[row][c].value == num) {
            return false;
        }
    }

    // ���ͬһ���Ƿ�����ظ�����
    for (int r = 0; r < SIZE; ++r) {
        if (board[r][col].value == num) {
            return false;
        }
    }

    // ���ͬһ3x3�����Ƿ�����ظ�����
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

// ����δ����ĵ�Ԫ��
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

// ������������������
bool generateBoard(Cell board[][SIZE]) {
    int row, col;

    if (!findUnassignedCell(board, row, col)) {
        // ������е�Ԫ���ѷ��䣬��ʾ�����ѽ��
        return true;
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(board, row, col, num)) {
            // ���Է�������
            board[row][col].value = num;

            if (generateBoard(board)) {
                // �ݹ���ʣ�����������
                return true;
            }

            // �����������ֵ��º����޽⣬�����
            board[row][col].value = 0;
        }
    }

    return false;
}


// ������������
void generatePuzzle(Cell board[][SIZE]) {
    // �ȸ�����������������
    Cell tempBoard[SIZE][SIZE];
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            tempBoard[row][col].value = board[row][col].value;
            tempBoard[row][col].given = true;
        }
    }

    // ���ȥ������
    int numGiven = SIZE * SIZE;  // �Ѹ������ֵ�����
    int numToRemove = rand() % 45 + 36;  // ��Ҫȥ����������������Χ��36��44֮�䣨��֤�н���Ψһ�⣩

    while (numGiven > SIZE * SIZE - numToRemove) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (tempBoard[row][col].given) {
            tempBoard[row][col].value = 0;
            tempBoard[row][col].given = false;
            numGiven--;
        }
    }

    // �����ɵ��������⸴�ƻ�ԭ����
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            board[row][col].value = tempBoard[row][col].value;
            board[row][col].given = tempBoard[row][col].given;
        }
    }
}

// �����������
bool solveSudoku(Cell board[][SIZE]) {
    int row, col;
    if (!findUnassignedCell(board, row, col)) {
        // ������е�Ԫ���ѷ��䣬��ʾ�����ѽ��
        return true;
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(board, row, col, num)) {
            // ���Է�������
            board[row][col].value = num;

            if (solveSudoku(board)) {
                // �ݹ���ʣ�����������
                return true;
            }

            // �����������ֵ��º����޽⣬�����
            board[row][col].value = 0;
        }
    }

    return false;
}

int main() {
    srand(time(nullptr));

    Cell board[SIZE][SIZE];

    // ������������������
    generateBoard(board);

    // ������������
    generatePuzzle(board);

    // ��ʾ��ʼ��������
    printBoard(board);

    // �����������
    solveSudoku(board);

    // ��ʾ��������������
    printBoard(board);

    return 0;
}
