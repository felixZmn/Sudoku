#include <stdio.h>
#include "point.h"
#include "stack/stack.h"
#include <time.h>

int gameBoard[9][9];
char playerName[256];

/*
 * print sudoku field
 */
void printField(){
    printf("Spieler: %s\n", playerName);

    printf("   abc def ghi\n");
    for(int i = 0; i < 9; i++){
        if(i%3==0){
            printf("   --- --- ---\n");
        }

        printf("%d ", i+1); // line numbers
        for(int j = 0; j < 9; j++){
            int value = gameBoard[i][j];
            if(j%3==0){
                printf("|");
            }
            if(value == 0){
                printf(" ");
            } else {
                printf("%d", value);
            }
        }
        printf("|\n");
    }
    printf("   --- --- ---\n");
}

/*
 * init the game board with zeros
 */
void initGameBoard(){
    for(int i = 0; i <= 8; i++){
        for(int j = 0; j <= 8; j++){
            gameBoard[i][j] = 0;
        }
    }
}

int checkSqare(point p, int v){
    int offsetX = p.x - p.x % 3;
    int offsetY = p.y - p.y % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(gameBoard[i + offsetX][j+offsetY] == v){
                return 0;
            }
        }
    }
    return 1;
}

int isValueValid(point p, int v){
    for(int i = 0; i < 9; i++){
        if(gameBoard[p.x][i] == v){
            return 0;
        }
    }
    for(int i = 0; i < 9; i++){
        if(gameBoard[i][p.y] == v){
            return 0;
        }
    }
    return checkSqare(p, v);
}

/*
 * save user inputted coordinate/value
 */
void saveValue(int x, int y, int value){
    gameBoard[x][y] = value;
}

int removeValue(int x, int y){
    int number = gameBoard[x][y];
    gameBoard[x][y] = 0;
    return number;
}

point getNewRandomPoint(){
    point p;
    do{
        int randomNumber = (rand() % 9);
        p.x = randomNumber;
        randomNumber = (rand() % 9);
        p.y = randomNumber;
    } while(0 != gameBoard[p.x][p.y]);

    return p;
}

/*
 * fill game board with random (correct) values
 */
void fillField(){
    myStack_t* stack;
    stack = StackNew(sizeof(point), 81 );
    int counter = 0; // currently found numbers
    int back = 0; //backtracking indicator
    int number = 1; // number to check
    point p;

    while(counter < 81){
        if(!back){
            p = getNewRandomPoint();
            number = 1;
        }

        int isValidNumber = 0;
        while (number < 10){
            if(isValueValid(p, number)){
                isValidNumber = 1;
                break;
            }
            number++;
        }

        if(isValidNumber){
            back = 0;
            saveValue(p.x, p.y, number);
            Push(stack, &p);
            counter++;
        } else {
            Pop(stack, &p);
            number = removeValue(p.x, p.y)+1;
            back = 1;
            counter--;
        }
    }
}

/*
 *
 */
int main(int argc, char** argv) {
    srand(time(0));
    initGameBoard();
    fillField();
    printf("Bitte Namen eingeben: ");
    scanf("%255[^\n]", playerName);
    printField();

    while(1){
        printf("Koordinate?\n");
        char inputCord[2];
        scanf(" %2[a-i1-9]s", inputCord);
        printf("Wert? (1-9)\n");
        int inputValue;
        scanf(" %1d", &inputValue);
        saveValue(inputCord[1] -'1', inputCord[0]-'a', inputValue);
        printField();
    }
    return 0;
}