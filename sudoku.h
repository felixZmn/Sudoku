//
// Created by felix on 27.01.2022.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include "types.h"


void setValue(int x, int y, int value);
int removeValue(int x, int y);
int getValue(int x, int y);
void initGameBoard();
int checkSqare(point p, int v);
int isValueValid(point p, int v);
void generateSudoku();

#endif //SUDOKU_SUDOKU_H
