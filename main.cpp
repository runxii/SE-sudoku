
#include <ctime>

#include "generate.h"



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


int main(int argc, char* argv[]) {
    testGenerateBoard();
    return 0;
}
