#include <ctime>
#include "solver.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: sudoku -c <number_of_games> -n <count> -s <filepath>" << std::endl;
        return 0;
    }

    std::string option = argv[1];
    std::string argument = argv[2];

    if (option == "-c") {
        generateMultipleBoard(stoi(argument));
    }
    else if (option == "-n") {
        generateMultipleSudoku(stoi(argument));
    }
    else if (option == "-s") {
        // 获取文件中数独游戏的个数
        int sudokuNum = loadSudokuNum(argument);
        solveSudokuGames(argument,sudokuNum);
        
    }
    else {
        std::cout << "Invalid option: " << option << std::endl;
    }
    return 0;
}
