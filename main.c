#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

char playerName[256];
int sudoku[9][9];

/**
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
            int value = getValue(i, j);
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
 *
 */
int main(int argc, char** argv) {
    srand(time(0));
    generateSudoku();
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
        printField();
    }
    return 0;
}
