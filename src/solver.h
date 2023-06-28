#pragma once
#include "generate.h"

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

// ��ָ��·�����ļ��ж�ȡ������Ϸ
//vector<vector<int>> loadSudokuFromFile(const std::string& filename, int index)
//{
//
//}
//
//// �����sudokuIndex����������
//void solveSudokuGames(const string& filename, int sudokuIndex) {
//    
//    for (int i = 0; i < sudokuIndex; i++) {
//        vector<vector<int>> needSolve = loadSudokuFromFile(filename,i);
//        // TODO
//    }
//}