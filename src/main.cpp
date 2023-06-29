#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "ʹ�÷���: ./sudoku.exe -c <number_of_games> -n <count> -r <min> <max> -n <count> -m <difficulty>" << endl;
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
            cout << sudokuCount << "��Ĭ��������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
        }
        else {
            string next_option = argv[3];
            if (next_option == "-u") {
                // ��Ҫȥ����������������Χ��36��44֮�䣨��֤�н���Ψһ�⣩
                int eraseCount = 0;
                eraseCount = rand() % 45 + 36;
                cout << sudokuCount << "����Ψһ���������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
            }
            else {
                string next_argument = argv[4];
                if (next_option == "-r")
                {
                    // �����ڿո��ӵ�������Χ����������Ϸ
                    int minErase = stoi(next_argument);
                    int maxErase = stoi(argv[5]);
                    int eraseCount = rand() % (maxErase - minErase + 1) + minErase;
                    cout << sudokuCount << "��ָ���ڿյ�������Ϸ�ѳɹ����ɣ�������generate.txt��\n��Ӧ���վ��ѱ��浽solveSheet.txt��" << endl;
                }
                else if (next_option == "-m") {
                    // �����Ѷȼ�������������Ϸ
                    int difficulty = stoi(next_argument);

                    if (difficulty < 1 || difficulty > 3) {
                        cout << "��Ч���Ѷȵȼ�������" << difficulty << endl;
                        return 0;
                    }

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
                    //generateMultipleSudoku(sudokuCount, eraseCount);
                    cout << sudokuCount << "���Ѷ�Ϊ" << difficulty << "��������Ϸ�ѳɹ����ɣ������浽generate.txt\n��Ӧ�վֱ��浽solveSheet.txt��" << endl;
                }
                else {
                    cerr << "��Ч������" << next_option << endl;
                    return 0;
                }
            }
        }
        generateMultipleSudoku(sudokuCount, eraseCount);
    }
    else if (option == "-s") {
        // ��ȡ�ļ���������Ϸ�ĸ���
        int sudokuNum = loadSudokuNum(argument);
        solveSudokuGames(argument,sudokuNum);
        cout << "�������ɣ��𰸱��浽sudoku.txt�У���鿴��" << endl;
    }
    else {
        cerr << "��Ч����: " << option << endl;
    }
    return 0;
}
