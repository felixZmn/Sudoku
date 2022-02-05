#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack/stack.h"
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
myStack_t* moves;

/**
 * saves user inputted solution
 * @param x x-coordinate
 * @param y y-coordinate
 * @param value value to set
 * @param checkRules 1 if the sudoku rules should be checked
 * @return zero if saving was successfull
 */
int setSolution(int x, int y, int value, int checkRules){
    if(gameBoard[x][y].generatedInput){
        return 1;
    } else {
        if(checkRules && solution[x][y] != value){
            return 1;
        }
        gameBoard[x][y].value = value;
        point p = {x, y};
        Push(moves, &p);
    }
    return 0;
}

int isSudokuSolved(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(gameBoard[i][j].value == 0){
                return 0;
            }
        }
    }
    return 1;
}

void prepareGameBoard(){
    int randomIterations = rand() % 19 + 17;
    for (int i = 0; i <= randomIterations; ++i) {
        point p = getRandomPoint();
        gameBoard[p.x][p.y].generatedInput = 1;
        gameBoard[p.x][p.y].value = solution[p.x][p.y];
    }
}

void undoMove(){
    point p;
    Pop(moves, &p);
    gameBoard[p.x][p.y].value = 0;
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
            entry value = gameBoard[i][j];
            if(j%3==0){
                printf("|");
            }
            if(value.generatedInput /*vorgabe*/){
                printf("%s%d%s", KBLU, value.value, KNRM);
            } else if (value.value == solution[i][j]/*nutzerwert korrekt*/){
                printf("%s%d%s", KGRN, value.value, KNRM);
            } else if (value.value == 0 /*kein nutzerwert vorhanden*/){
                printf("%s%d%s", KNRM, solution[i][j], KNRM);
            } else /*nutzerwert falsch, lösung rot einblenden*/{
                printf("%s%d%s", KRED, solution[i][j], KNRM);
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

/**
 * prints a game menu
 * @return selected menu value
 */
int printMenu(){
    int inputValue;
    do{
        printf("Menu:\n");
        printf("1 -> undo\n");
        printf("2 -> Regelpruefung aktivieren\n");
        printf("3 -> Regelpruefung deaktivieren\n");
        printf("4 -> Loesung ausgeben\n");
        printf("5 -> menu schliessen\n");
        printf("9 -> Spiel beenden\n");
        scanf(" %1d", &inputValue);
    } while (!(inputValue > 0 && inputValue <= 4 || inputValue == 9));
    return inputValue;
}

/*
 *
 */
int main(int argc, char** argv) {
    moves = StackNew(sizeof(point), 81 );
    int checkRules = 1;
    srand(time(0));
    generateSolution();
    printf("Bitte Namen eingeben: ");
    scanf("%255[^\n]", playerName);
    prepareGameBoard();
    printGameBoard();

    while(!isSudokuSolved()){
        char input[3];
        do{
            printf("Bitte Koordinate [a-f1-9] eingeben oder Menue [m] oeffnen\n");
            scanf(" %2s", input);
        } while (!(input[0] >= 97 && input[0] <= 105 && input[1] >= 49 && input[1] <= 57 || input[0] == 'm' ));
        if ('m' == input[0]){
            switch (printMenu()) {
                case 1:
                    undoMove();
                    break;
                case 2:
                    checkRules = 1;
                    break;
                case 3:
                    checkRules = 0;
                    break;
                case 4:
                    printSolution();
                    break;
                case 5:
                    // intentionally empty
                    break;
                case 9:
                    exit(0);
                default:
                    break;
            }
        } else{
            int inputValue;
            do{
                printf("Wert? [1-9]\n");
                scanf(" %1d", &inputValue);
            } while (!(inputValue > 0 && inputValue <= 9));
            if(setSolution(input[1] - '0' -1, input[0] - 'a', inputValue, checkRules)){
                printf("Ungueltige Koordinate");
            }
        }
        printGameBoard();
    }
    return 0;
}
