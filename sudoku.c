//
// Created by felix on 27.01.2022.
//

#include "stack/stack.h"
#include "sudoku.h"
#include "types.h"
#include "helpers.h"

extern int sudoku[9][9];

/**
 * save
 * @param x x value of coordinate
 * @param y y value of coordinate
 * @param value value to put in grid
 */
void setValue(int x, int y, int value){
    sudoku[x][y] = value;
}

/**
 *
 * @param x x value of coordinate
 * @param y y value of coordinate
 * @return deleted value
 */
int removeValue(int x, int y){
    int number = sudoku[x][y];
    sudoku[x][y] = 0;
    return number;
}

int getValue(int x, int y){
    return sudoku[x][y];
}

/**
 * fill the game board with zeroes
 */
void initGameBoard(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            setValue(i, j, 0);
        }
    }
}

int checkSqare(point p, int v){
    int offsetX = p.x - p.x % 3;
    int offsetY = p.y - p.y % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(getValue(i + offsetX,j+offsetY ) == v){
                return 0;
            }
        }
    }
    return 1;
}

/**
 * checks if a value can be assigned to a point without violating the sudoku rules
 * These rules are:
 * a value has to be unique on a row, on a line and in the 3x3 square
 * @param p point to check
 * @param v value to check
 * @return 0 if the value is forbidden <br>
 * 1 if the value can be assigned to the point without violating the rules
 */
int isValueValid(point p, int v){
    for(int i = 0; i < 9; i++){
        if(getValue(p.x, i) == v){
            return 0;
        }
        if(getValue(i,p.y) == v){
            return 0;
        }
    }
    return checkSqare(p, v);
}

/**
 * generates a complete filled sudoku
 */
void generateSudoku(){
    myStack_t* stack;
    stack = StackNew(sizeof(point), 81 );
    int counter = 0; // currently found numbers
    int back = 1; //backtracking indicator
    int number; // number to check
    point p;

    initGameBoard();

    while(counter < 81){
        do{
            p = getNewRandomPoint();
        } while(0 != getValue(p.x, p.y));

        number = 1;
        int isValidNumber = 0;
        while (number < 10){
            if(isValueValid(p, number)){
                isValidNumber = 1;
                break;
            }
            number++;
        }

        if(isValidNumber){
            back = 1;
            setValue(p.x, p.y, number);
            Push(stack, &p);
            counter++;
        } else {
            back = back * 4;
            for (int i = 0; i < back && counter != 0; ++i) {
                Pop(stack, &p);
                removeValue(p.x, p.y);
                counter--;
            }
        }
    }
}