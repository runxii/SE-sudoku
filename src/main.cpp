#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "使用方法: ./sudoku.exe -c <number_of_games> -n <count> -r <min> <max> -n <count> -m <difficulty>" << endl;
        return 0;
    }

    string option = argv[1];
    string argument = argv[2];

    if (option == "-c") {
        generateMultipleBoard(stoi(argument));
    }
    else if (option == "-n") {

        int sudokuCount = stoi(argument);
        int eraseCount = ERASE;
        if (argc < 4) {
            //generateMultipleSudoku(sudokuCount, eraseCount);
            cout << sudokuCount << "个默认数独游戏已成功生成，并保存generate.txt中\n对应的终局已保存到solveSheet.txt中" << endl;
        }
        else {
            string next_option = argv[3];
            if (next_option == "-u") {
                // 需要去除的数字数量，范围在36到44之间（保证有解且唯一解）
                eraseCount = 0;
                eraseCount = rand() % 45 + 36;
                cout << sudokuCount << "个有唯一解的数独游戏已成功生成，并保存generate.txt中\n对应的终局已保存到solveSheet.txt中" << endl;
            }
            else {
                string next_argument = argv[4];
                if (next_option == "-r")
                {
                    // 按照挖空格子的数量范围生成数独游戏
                    int minErase = stoi(next_argument);
                    int maxErase = stoi(argv[5]);
                    eraseCount = rand() % (maxErase - minErase + 1) + minErase;
                    cout << sudokuCount << "个指定挖空的数独游戏已成功生成，并保存generate.txt中\n对应的终局已保存到solveSheet.txt中" << endl;
                }
                else if (next_option == "-m") {
                    // 按照难度级别生成数独游戏
                    int difficulty = stoi(next_argument);

                    if (difficulty < 1 || difficulty > 3) {
                        cout << "无效的难度等级参数：" << difficulty << endl;
                        return 0;
                    }

                    switch (difficulty) {
                    case 1:
                        eraseCount = 30; // 简单级别，30个空格
                        break;
                    case 2:
                        eraseCount = 45; // 中级别，45个空格
                        break;
                    case 3:
                        eraseCount = 60; // 高级别，60个空格
                        break;
                    }
                    //generateMultipleSudoku(sudokuCount, eraseCount);
                    cout << sudokuCount << "个难度为" << difficulty << "的数独游戏已成功生成，并保存到generate.txt\n对应终局保存到solveSheet.txt中" << endl;
                }
                else {
                    cerr << "无效参数：" << next_option << endl;
                    return 0;
                }
            }
        }
        generateMultipleSudoku(sudokuCount, eraseCount);
    }
    else if (option == "-s") {
        // 获取文件中数独游戏的个数
        int sudokuNum = loadSudokuNum(argument);
        solveSudokuGames(argument,sudokuNum);
        cout << "解决已完成，答案保存到sudoku.txt中，请查看。" << endl;
    }
    else {
        cerr << "无效参数: " << option << endl;
    }
    return 0;
}
