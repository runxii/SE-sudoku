#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include <algorithm>
#include "testPuzzle.h"

using namespace std;

// �������̴�СΪ9*9
const int SIZE = 9;
// û����������ʱ��Ĭ�ϴ�һ���վ����ڿ�40�����ӵõ�һ��������������Ϸ
const int ERASE = 40;
const string generateFilename = "generate.txt";
const string solveSheetFilename = "solveSheet.txt";

void print(const vector<vector<int>>& num)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (num[i][j] == -1) {
                // �ո�Ӧ�����$
                cout << "$ ";
            }
            else {
                cout << num[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool IsRightPlace(vector<vector<int>>& num, int row, int col)
{
    int n = num[row][col];
    //ע��i < row
    for (int i = 0; i < row; i++)
    {
        if (num[i][col] == n)
            return false;
    }
    //ע��i < col
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
    //ע�� k <= 8
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
            //ע��j = col_start ����Ҫ�����ʱ�е���ʼ�㣡
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

// ����n�������վ�
void generateMultipleBoard(int n) {
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < n; i++) {
        vector<vector<int>> num(SIZE, vector<int>(SIZE, -1));
        generate_core(num, 0, 0);

        cout << "Sudoku board " << (i + 1) << ":\n";
        print(num);
        cout << endl;
    }
}

void eraseRandomGrids(vector<vector<int>>& num, int count) {
    vector<pair<int, int>> positions;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            positions.emplace_back(i, j);
        }
    }

    random_shuffle(positions.begin(), positions.end());

    for (int i = 0; i < count; i++) {
        int row = positions[i].first;
        int col = positions[i].second;
        num[row][col] = -1;
    }
}

// �����ɵ�������Ϸд��ָ���ļ�
// sudokuIndex�����ɵĵڼ�����Ϸ
void saveSudokuToFile(const vector<vector<int>>& num, const string& filename, int sudokuIndex) {
    // ��׷��ģʽ���ļ�
    ofstream outFile(filename, ios::app); 

    if (outFile.is_open()) {
        outFile << "--------" << sudokuIndex << "--------" << endl;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (num[i][j] == -1) {
                    outFile << "$ ";
                }
                else {
                    outFile << num[i][j] << " ";
                }
            }
            outFile << endl;
        }

        outFile.close(); // �ر�����ļ�
        //cout << "��" << sudokuIndex << "�������ɹ����浽�������ļ��У�" << filename << endl;
    }
    else {
        cerr << "�޷���ָ���ļ�" << filename << endl;
    }
}

// ����n��������������Ϸ
void generateMultipleSudoku(int n, int eraseNum) {
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < n; i++) {
        vector<vector<int>> num(SIZE, vector<int>(SIZE, -1));
        generate_core(num, 0, 0);
        saveSudokuToFile(num, solveSheetFilename, i + 1);

        eraseRandomGrids(num, eraseNum);
        saveSudokuToFile(num, generateFilename, i + 1);
    }
}