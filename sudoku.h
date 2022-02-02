//
// Created by felix on 27.01.2022.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include "types.h"


void setSolutionValue(int x, int y, int value);
int removeSolutionValue(int x, int y);
int getSolutionValue(int x, int y);
int checkSqare(point p, int v);
int isValueValid(point p, int v);
void generateSolution();

#endif //SUDOKU_SUDOKU_H
