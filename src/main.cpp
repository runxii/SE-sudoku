#pragma warning(disable:4530)
#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "ERROR: 参数缺失" << endl;
        cout << "USAGE: ./sudoku.exe -c <number_of_games> \n"
            << "                    -s <path_to_file> \n"
            << "                    -n <count>\n"
            << "                    -n <count> -r <min> <max>\n"
            << "                    -n <count> -u\n"
            << "                    -n <count> -m <difficulty>" << endl;
    }
    else {
        string option = argv[1];
        string argument = argv[2];

        if (option == "-c") {
            if (stoi(argument) >= 1000000 || stoi(argument) <= 0)
                cerr << "ERROR: -c <number_of_games> 参数范围为0~1,000,000" << endl;
            else
                generateMultipleBoard(stoi(argument));
        }
        else if (option == "-n") {
            // atoi不报错，而是返回0
            if (atoi(argument.c_str()) == 0)
                cerr << "ERROR: -n之后的参数类型错误，请输入一个在0~10,000的整数" << endl;
            else {
                int sudokuCount = stoi(argument);
                int eraseCount = ERASE;
                if (argc == 3) {
                    if (sudokuCount > 0 && sudokuCount < 10000)
                        cout << sudokuCount << "个默认数独游戏已成功生成，并保存generate.txt中\n对应的终局已保存到solveSheet.txt中" << endl;
                    else
                        cerr << "ERROR: -n之后的参数范围错误，请输入一个在0~10,000之间的整数" << endl;
                }
                else {
                    string next_option = argv[3];
                    if (next_option == "-u") {
                        if (argc > 4)
                            cerr << "ERROR: -u的参数过多" << endl;
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
                            if (atoi(next_argument.c_str()) * atoi(argv[5]) != 0) {
                                int minErase = stoi(next_argument);
                                int maxErase = stoi(argv[5]);
                                if (minErase < maxErase && minErase >= 20 && maxErase <= 55) {
                                    eraseCount = rand() % (maxErase - minErase + 1) + minErase;
                                    cout << sudokuCount << "个指定挖空的数独游戏已成功生成，并保存generate.txt中\n对应的终局已保存到solveSheet.txt中" << endl;
                                }
                                else
                                    cerr << "ERROR: -r的参数范围错误，请从小到大输入20~55之间的两个整数" << endl;
                            }
                            else
                                cerr << "ERROR: -r的参数无效" << endl;

                        }
                        else if (next_option == "-m") {
                            // 按照难度级别生成数独游戏
                            int difficulty = stoi(next_argument);

                            if (difficulty < 1 || difficulty > 3)
                                cout << "无效的难度等级参数：" << difficulty << endl;

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
                            cout << sudokuCount << "个难度为" << difficulty << "的数独游戏已成功生成，并保存到generate.txt\n对应终局保存到solveSheet.txt中" << endl;
                        }
                        else
                            cerr << "无效参数：" << next_option << endl;
                    }
                }
                generateMultipleSudoku(sudokuCount, eraseCount);
            }
        }
        else if (option == "-s") {
            // 获取文件中数独游戏的个数
            int sudokuNum = loadSudokuNum(argument);
            if (sudokuNum == 0)
                cerr << "ERROR: 文件中的数独并不完整，请检查" << endl;
            else {
                solveSudokuGames(argument, sudokuNum);
                cout << "解决已完成，答案保存到sudoku.txt中，请查看。" << endl;
            }
        }
        else
            cerr << "ERROR: 无效参数 " << option << endl;
    }
    return 0;
}
