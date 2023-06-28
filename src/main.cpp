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
            // 按照挖空格子的数量范围生成数独游戏
            int minErase = std::stoi(next_argument);
            int maxErase = std::stoi(argv[5]);
            int randomErase = rand() % (maxErase - minErase + 1) + minErase;

            generateMultipleSudoku(sudokuCount, randomErase);
        }
        else if (next_option == "-m") {
            // 按照难度级别生成数独游戏
            int difficulty = std::stoi(next_argument);
            int eraseCount = ERASE;
            if (difficulty < 1 || difficulty > 3) {
                std::cout << "Invalid difficulty level: " << difficulty << std::endl;
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
            generateMultipleSudoku(sudokuCount, eraseCount);
            cout << sudokuCount << " Sudoku game(s) of difficulty level " << difficulty << " generated and saved to game.txt" << std::endl;
        }
        else {
            std::cout << "Invalid option: " << option << std::endl;
            return 0;
        }
    }
    else if (option == "-s") {
        // 获取文件中数独游戏的个数
        int sudokuNum = loadSudokuNum(argument);
        //solveSudokuGames(argument,sudokuNum);
        
    }
    else {
        std::cout << "Invalid option: " << option << std::endl;
    }
    return 0;
}
