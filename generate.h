#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include "puzzle.h"


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

// ���� generateBoard ����
void testGenerateBoard() {
    Cell test[9][9];
    

    // ���� generateBoard ����
    generateBoard(test);

    // ������ɵ�������Ϸ�Ƿ��������

    // ���ÿ���Ƿ�����Ψһ��
    for (int i = 0; i < 9; i++) {
        int count[10] = { 0 }; // ��¼���ֳ��ֵĴ���
        for (int j = 0; j < 9; j++) {
            int num = test[i][j].value;
            assert(num >= 1 && num <= 9); // ����Ӧ����Ч��Χ��
            count[num]++;
            assert(count[num] == 1); // �����ڵ�ǰ����ֻ�ܳ���һ��
        }
    }

    // ���ÿ���Ƿ�����Ψһ��
    for (int j = 0; j < 9; j++) {
        int count[10] = { 0 }; // ��¼���ֳ��ֵĴ���
        for (int i = 0; i < 9; i++) {
            int num = test[i][j].value;
            assert(num >= 1 && num <= 9); // ����Ӧ����Ч��Χ��
            count[num]++;
            assert(count[num] == 1); // �����ڵ�ǰ����ֻ�ܳ���һ��
        }
    }

    // ���ÿ��С�Ź����Ƿ�����Ψһ��
    for (int blockRow = 0; blockRow < 3; blockRow++) {
        for (int blockCol = 0; blockCol < 3; blockCol++) {
            int count[10] = { 0 }; // ��¼���ֳ��ֵĴ���
            for (int i = blockRow * 3; i < blockRow * 3 + 3; i++) {
                for (int j = blockCol * 3; j < blockCol * 3 + 3; j++) {
                    int num = test[i][j].value;
                    assert(num >= 1 && num <= 9); // ����Ӧ����Ч��Χ��
                    count[num]++;
                    assert(count[num] == 1); // �����ڵ�ǰС�Ź�����ֻ�ܳ���һ��
                }
            }
        }
    }

    std::cout << "generateBoard function passed the test.\n";
}