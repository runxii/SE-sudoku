#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: sudoku -c <number_of_games> -n <count> -r <min> <max> -n <count> -m <difficulty>" << std::endl;
        return 0;
    }

    std::string option = argv[1];
    std::string argument = argv[2];

    if (option == "-c") {
        generateMultipleBoard(stoi(argument));
    }
    else if (option == "-n") {

        int sudokuCount = std::stoi(argument);

        if (argc < 4) {
            generateMultipleSudoku(sudokuCount, ERASE);
            
        }
        
        std::string next_option = argv[3];
        std::string next_argument = argv[4];  

        if (next_option == "-r") 
        {
            // �����ڿո��ӵ�������Χ����������Ϸ
            int minErase = std::stoi(next_argument);
            int maxErase = std::stoi(argv[5]);
            int randomErase = rand() % (maxErase - minErase + 1) + minErase;

            generateMultipleSudoku(sudokuCount, randomErase);
        }
        else if (next_option == "-m") {
            // �����Ѷȼ�������������Ϸ
            int difficulty = std::stoi(next_argument);
            int eraseCount = ERASE;
            if (difficulty < 1 || difficulty > 3) {
                std::cout << "Invalid difficulty level: " << difficulty << std::endl;
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
            generateMultipleSudoku(sudokuCount, eraseCount);
            cout << sudokuCount << " Sudoku game(s) of difficulty level " << difficulty << " generated and saved to game.txt" << std::endl;
        }
        else {
            std::cout << "Invalid option: " << option << std::endl;
            return 0;
        }
    }
    else if (option == "-s") {
        // ��ȡ�ļ���������Ϸ�ĸ���
        int sudokuNum = loadSudokuNum(argument);
        //solveSudokuGames(argument,sudokuNum);
        
    }
    else {
        std::cout << "Invalid option: " << option << std::endl;
    }
    return 0;
}
