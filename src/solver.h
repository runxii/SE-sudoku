#pragma once
#include "generate.h"
#include <sstream>

const string answerFilename = "sudoku.txt";

// 统计该文件中一共有多少个数独游戏，返回int sudokuIndex
int loadSudokuNum(const string& filename) {
    ifstream inFile(filename);
    int lineno = 0;
    int sudokuIndex = 0;
    if (inFile.is_open()) {
        // 文件总行数

        string line;
        vector<vector<int>> sudokuGame;
        while (getline(inFile, line)) {
            lineno++;
        }
    }
    else {
        cerr << "Unable to open file " << filename << endl;
    }
    // 数独有缺行
    if (lineno % (SIZE + 1) != 0) {
        cerr << "Sudokus in File are not complete " << endl;
    }
    else {
        sudokuIndex = lineno / 10;
    }
    cout << "文件里一共有" << sudokuIndex << "个数独游戏待解决" << endl;
    return sudokuIndex;
}

 //从指定路径的文件中读取数独游戏
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

    // 从指定行开始读取数据，读取十行则代表一个数独
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

    // 对puzzles进行resize，变为9*9的二维向量
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = puzzles[0][i * 9 + j];
        }
    }

    return result;
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    // 检查行是否安全
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // 检查列是否安全
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // 检查小九宫格是否安全
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

                        board[row][col] = -1;  // 回溯
                    }
                }

                return false;  // 所有数字都尝试过都无法解决，返回 false
            }
        }
    }

    return true;  // 数独已经解决
}


 //解决共sudokuIndex个数独问题
void solveSudokuGames(const string& filename, int sudokuIndex) {
    
    for (int i = 0; i < sudokuIndex; i++) {
        vector<vector<int>> needSolve = loadSudokuFromFile(filename,i+1);
        // TODO
        if (solveSudoku(needSolve)) {
            // 解决数独游戏，写入sudoku.txt中
            saveSudokuToFile(needSolve, answerFilename, i + 1);
        }
        else {
            cout << "无解" << endl;
            exit(1);
        }
    }
}