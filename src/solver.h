#pragma once
#include "generate.h"

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

// 从指定路径的文件中读取数独游戏
//vector<vector<int>> loadSudokuFromFile(const std::string& filename, int index)
//{
//
//}
//
//// 解决共sudokuIndex个数独问题
//void solveSudokuGames(const string& filename, int sudokuIndex) {
//    
//    for (int i = 0; i < sudokuIndex; i++) {
//        vector<vector<int>> needSolve = loadSudokuFromFile(filename,i);
//        // TODO
//    }
//}