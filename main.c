#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"
#include "helpers.h"

// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
#define KNRM  "\x1B[0m"    // normal
#define KRED  "\x1B[31m"   // red
#define KGRN  "\x1B[32m"   // green
#define KYEL  "\x1B[33m"   // yellow
#define KBLU  "\x1B[34m"   // blue
#define KMAG  "\x1B[35m"   // magenta
#define KCYN  "\x1B[36m"   // cyab
#define KWHT  "\x1B[37m"   // white

char playerName[256];
int solution[9][9];
entry gameBoard[9][9] = {0};

void prepareGameBoard(){
    int randomIterations = rand() % 19 + 17;
    for (int i = 0; i <= randomIterations; ++i) {
        point p = getRandomPoint();
        gameBoard[p.x][p.y].generatedInput = 1;
        gameBoard[p.x][p.y].value = solution[p.x][p.y];
    }
}

/**
 * print solution field
 */
void printSolution(){
    printf("Spieler: %s\n", playerName);
    printf("   abc def ghi\n");
    for(int i = 0; i < 9; i++){
        if(i%3==0){
            printf("   --- --- ---\n");
        }

        printf("%d ", i+1); // line numbers
        for(int j = 0; j < 9; j++){
            int value = getSolutionValue(i,j);
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

/**
 * print current game board
 */
void printGameBoard(){
    printf("Spieler: %s\n", playerName);
    printf("   abc def ghi\n");
    for(int i = 0; i < 9; i++){
        if(i%3==0){
            printf("   --- --- ---\n");
        }

        printf("%d ", i+1); // line numbers
        for(int j = 0; j < 9; j++){
            entry value = gameBoard[i][j];
            if(j%3==0){
                printf("|");
            }
            if(value.value == 0){
                printf(" ");
            } else if(value.generatedInput) {
                // generierter wert, andere farbe notwendig
                printf("%s%d%s", KBLU, value.value, KNRM);
            } else{
                printf("%d", value.value);
            }
        }
        printf("|\n");
    }
    printf("   --- --- ---\n");
}

/*
 *
 */
int main(int argc, char** argv) {
    srand(time(0));
    generateSolution();
    printf("Bitte Namen eingeben: ");
    scanf("%255[^\n]", playerName);
    prepareGameBoard();
    printGameBoard();

    while(1){
        printf("Koordinate?\n");
        char inputCord[2];
        scanf(" %2[a-i1-9]s", inputCord);
        printf("Wert? (1-9)\n");
        int inputValue;
        scanf(" %1d", &inputValue);
        printGameBoard();
    }
    return 0;
}
