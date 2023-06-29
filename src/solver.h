#pragma once
#include "generate.h"
#include <sstream>

const string answerFilename = "sudoku.txt";

// ͳ�Ƹ��ļ���һ���ж��ٸ�������Ϸ������int sudokuIndex
int loadSudokuNum(const string& filename) {
    ifstream inFile(filename);
    int lineno = 0;
    int sudokuIndex = 0;
    if (inFile.is_open()) {
        // �ļ�������

        string line;
        vector<vector<int>> sudokuGame;
        while (getline(inFile, line)) {
            lineno++;
        }
    }
    else {
        cerr << "Unable to open file " << filename << endl;
    }
    // ������ȱ��
    if (lineno % (SIZE + 1) != 0) {
        cerr << "Sudokus in File are not complete " << endl;
    }
    else {
        sudokuIndex = lineno / 10;
    }
    cout << "�ļ���һ����" << sudokuIndex << "��������Ϸ�����" << endl;
    return sudokuIndex;
}

 //��ָ��·�����ļ��ж�ȡ������Ϸ
vector<vector<int>> loadSudokuFromFile(const string& filename, int index)
{
    //vector<vector<int>> sudokuFromFile;
    //ifstream InFile(filename);

    //if (!InFile.is_open()) {
    //    cerr << "Failed to open the file." << endl;
    //    exit(1);
    //}
    //string line;
    ifstream InFile(filename);
    if (!InFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return {};
    }

    vector<vector<int>> puzzles;
    vector<vector<int>> result(SIZE, vector<int>(SIZE));
    string line;
    vector<int> puzzle;

    int startLine = (index-1)*(SIZE+1)+2;
    int currentLine = 1;

    // ��ָ���п�ʼ��ȡ���ݣ���ȡʮ�������һ������
    while (getline(InFile, line) && (currentLine<startLine+SIZE)) {
        if (currentLine >= startLine) {
            if (line.empty()) {
                continue;
            }

            istringstream iss(line);
            string token;
            while (iss >> token) {
                if (token == "$") {
                    puzzle.push_back(-1);
                }
                else {
                    puzzle.push_back(stoi(token));
                }
            }
        }
        currentLine++;
    }

    if (!puzzle.empty()) {
        puzzles.push_back(puzzle);
    }

    InFile.close();

    // ��puzzles����resize����Ϊ9*9�Ķ�ά����
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = puzzles[0][i * 9 + j];
        }
    }

    return result;
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    // ������Ƿ�ȫ
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // ������Ƿ�ȫ
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // ���С�Ź����Ƿ�ȫ
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == -1) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        board[row][col] = -1;  // ����
                    }
                }

                return false;  // �������ֶ����Թ����޷���������� false
            }
        }
    }

    return true;  // �����Ѿ����
}


 //�����sudokuIndex����������
void solveSudokuGames(const string& filename, int sudokuIndex) {
    
    for (int i = 0; i < sudokuIndex; i++) {
        vector<vector<int>> needSolve = loadSudokuFromFile(filename,i+1);
        // TODO
        if (solveSudoku(needSolve)) {
            // ���������Ϸ��д��sudoku.txt��
            saveSudokuToFile(needSolve, answerFilename, i + 1);
        }
        else {
            cout << "�޽�" << endl;
            exit(1);
        }
    }
}