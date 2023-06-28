#pragma once
//定义的常量和结构

// 数独棋盘大小为9*9
const int SIZE = 9;

// 数独单元格的结构体
struct Cell {
    int value;
    bool given;
};