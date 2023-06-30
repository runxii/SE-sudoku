#pragma warning(disable:4530)
#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "ERROR: ����ȱʧ" << endl;
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
                cerr << "ERROR: -c <number_of_games> ������ΧΪ0~1,000,000" << endl;
            else
                generateMultipleBoard(stoi(argument));
        }
        else if (option == "-n") {
            // atoi���������Ƿ���0
            if (atoi(argument.c_str()) == 0)
                cerr << "ERROR: -n֮��Ĳ������ʹ���������һ����0~10,000������" << endl;
            else {
                int sudokuCount = stoi(argument);
                int eraseCount = ERASE;
                if (argc == 3) {
                    if (sudokuCount > 0 && sudokuCount < 10000)
                        cout << sudokuCount << "��Ĭ��������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
                    else
                        cerr << "ERROR: -n֮��Ĳ�����Χ����������һ����0~10,000֮�������" << endl;
                }
                else {
                    string next_option = argv[3];
                    if (next_option == "-u") {
                        if (argc > 4)
                            cerr << "ERROR: -u�Ĳ�������" << endl;
                        // ��Ҫȥ����������������Χ��36��44֮�䣨��֤�н���Ψһ�⣩
                        eraseCount = 0;
                        eraseCount = rand() % 45 + 36;
                        cout << sudokuCount << "����Ψһ���������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
                    }
                    else {
                        string next_argument = argv[4];
                        if (next_option == "-r")
                        {
                            // �����ڿո��ӵ�������Χ����������Ϸ
                            if (atoi(next_argument.c_str()) * atoi(argv[5]) != 0) {
                                int minErase = stoi(next_argument);
                                int maxErase = stoi(argv[5]);
                                if (minErase < maxErase && minErase >= 20 && maxErase <= 55) {
                                    eraseCount = rand() % (maxErase - minErase + 1) + minErase;
                                    cout << sudokuCount << "��ָ���ڿյ�������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
                                }
                                else
                                    cerr << "ERROR: -r�Ĳ�����Χ�������С��������20~55֮�����������" << endl;
                            }
                            else
                                cerr << "ERROR: -r�Ĳ�����Ч" << endl;

                        }
                        else if (next_option == "-m") {
                            // �����Ѷȼ�������������Ϸ
                            int difficulty = stoi(next_argument);

                            if (difficulty < 1 || difficulty > 3)
                                cout << "��Ч���Ѷȵȼ�������" << difficulty << endl;

                            switch (difficulty) {
                            case 1:
                                eraseCount = 30; // �򵥼���30���ո�
                                break;
                            case 2:
                                eraseCount = 45; // �м���45���ո�
                                break;
                            case 3:
                                eraseCount = 60; // �߼���60���ո�
                                break;
                            }
                            cout << sudokuCount << "���Ѷ�Ϊ" << difficulty << "��������Ϸ�ѳɹ����ɣ������浽generate.txt\n��Ӧ�վֱ��浽solveSheet.txt��" << endl;
                        }
                        else
                            cerr << "��Ч������" << next_option << endl;
                    }
                }
                generateMultipleSudoku(sudokuCount, eraseCount);
            }
        }
        else if (option == "-s") {
            // ��ȡ�ļ���������Ϸ�ĸ���
            int sudokuNum = loadSudokuNum(argument);
            if (sudokuNum == 0)
                cerr << "ERROR: �ļ��е�������������������" << endl;
            else {
                solveSudokuGames(argument, sudokuNum);
                cout << "�������ɣ��𰸱��浽sudoku.txt�У���鿴��" << endl;
            }
        }
        else
            cerr << "ERROR: ��Ч���� " << option << endl;
    }
    return 0;
}
