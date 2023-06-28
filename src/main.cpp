#include <ctime>
#include "generate.h"

int main(int argc, char* argv[]) {
    if (argc != 3 || (std::string(argv[1]) != "-c" && std::string(argv[1]) != "-n")) {
        std::cout << "Usage: sudoku -c <number> or sudoku -n <number>\n"
            << "Example: sudoku -c 5\n"
            << "         sudoku -n 10\n";
        return 1;
    }

    int n = std::atoi(argv[2]);
    if (n <= 0) {
        std::cout << "Invalid number of Sudoku boards.\n";
        return 1;
    }

    if (std::string(argv[1]) == "-c") {
        generateMultipleSudoku(n);
    }
    else if (std::string(argv[1]) == "-n") {
        for (int i = 0; i < n; i++) {
            std::vector<std::vector<int>> num(SIZE, std::vector<int>(SIZE, -1));
            generate_core(num, 0, 0);

            std::cout << "Sudoku game " << (i + 1) << ":\n";
            print(num);
            std::cout << std::endl;
        }
    }

    return 0;
}
