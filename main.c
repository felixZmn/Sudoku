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

int checkGameBoardSquare(point p, int v);
int isUserInputValueValid(point p, int v);
int setSolution(int x, int y, int value, int checkRules);
int isSudokuSolved();
void prepareGameBoard();
void undoMove();
void printSolution();
void printGameBoard();
int printMenu();

char playerName[256];
int solution[9][9];
entry gameBoard[9][9] = {0};
myStack_t *moves;

int main(int argc, char **argv) {
    moves = StackNew(sizeof(point), 81);
    int checkRules = 1;
    srand(time(0));
    generateSolution();
    printf("Bitte Namen eingeben: ");
    scanf("%255[^\n]", playerName);
    prepareGameBoard();
    printGameBoard();

    while (!isSudokuSolved()) {
        char input[3];
        do {
            printf("Bitte Koordinate [a-f1-9] eingeben oder Menue [m] oeffnen\n");
            scanf(" %2s", input);
        } while (!(input[0] >= 97 && input[0] <= 105 && input[1] >= 49 && input[1] <= 57 || input[0] == 'm'));
        if ('m' == input[0]) {
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
        } else {
            int inputValue;
            do {
                printf("Wert? [1-9]\n");
                scanf(" %1d", &inputValue);
            } while (!(inputValue > 0 && inputValue <= 9));
            if (setSolution(input[1] - '0' - 1, input[0] - 'a', inputValue, checkRules)) {
                printf("Ungueltige Koordinate oder Eingabe, die gegen die Relgeln von Sudoku verstoesst\n");
            }
        }
        printGameBoard();
    }
    return 0;
}

/**
 * checks if a user inputted value respects the basic sudoku rules
 * @param p point to check
 * @param v value to check
 * @return 0 if the input is not allowed, 1 if the value is allowed
 */
int isUserInputValueValid(point p, int v) {
    for (int i = 0; i < 9; i++) {
        if (gameBoard[p.x][i].value == v) {
            return 0;
        }
        if (gameBoard[i][p.y].value == v) {
            return 0;
        }
    }
    return checkGameBoardSquare(p, v);
}

/**
 * helper function to check user input
 * @param p point to check
 * @param v value to check
 * @return 0 if the input is not allowed, 1 if the value is allowed
 */
int checkGameBoardSquare(point p, int v) {
    int offsetX = p.x - p.x % 3;
    int offsetY = p.y - p.y % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (gameBoard[i + offsetX][j + offsetY].value == v) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * saves user inputted solution
 * @param x x-coordinate
 * @param y y-coordinate
 * @param value value to set
 * @param checkRules 1 if the sudoku rules should be checked
 * @return zero if saving was successfull
 */
int setSolution(int x, int y, int value, int checkRules) {
    if (gameBoard[x][y].generatedInput) {
        return 1;
    } else {
        point p = {x, y};
        if (checkRules && !isUserInputValueValid(p, value)) {
            return 1;
        }
        gameBoard[x][y].value = value;
        Push(moves, &p);
    }
    return 0;
}

/**
 * checks if the user has solved the full sudoku
 * @return 1 if every field is filled
 */
int isSudokuSolved() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (gameBoard[i][j].value == 0) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * chooses a random number of points from the solution and
 * copies them to the game board.
 */
void prepareGameBoard() {
    int randomIterations = rand() % 19 + 17;
    for (int i = 0; i <= randomIterations; ++i) {
        point p = getRandomPoint();
        gameBoard[p.x][p.y].generatedInput = 1;
        gameBoard[p.x][p.y].value = solution[p.x][p.y];
    }
}

void undoMove() {
    point p;
    Pop(moves, &p);
    gameBoard[p.x][p.y].value = 0;
}

/**
 * prints a complete solution.
 * the user inputted values are validated and colorized against this solution
 * BLUE: given value
 * RED: user input is wrong
 * GREEN: user input is correct
 * NO COLOR: field is filled with a value from the generated solution
 */
void printSolution() {
    printf("Spieler: %s\n", playerName);
    printf("   abc def ghi\n");
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("   --- --- ---\n");
        }

        printf("%d ", i + 1); // line numbers
        for (int j = 0; j < 9; j++) {
            entry value = gameBoard[i][j];
            if (j % 3 == 0) {
                printf("|");
            }
            if (value.generatedInput /*vorgabe*/) {
                printf("%s%d%s", KBLU, value.value, KNRM);
            } else if (value.value == solution[i][j]/*nutzerwert korrekt*/) {
                printf("%s%d%s", KGRN, value.value, KNRM);
            } else if (value.value == 0 /*kein nutzerwert vorhanden*/) {
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
void printGameBoard() {
    printf("Spieler: %s\n", playerName);
    printf("   abc def ghi\n");
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("   --- --- ---\n");
        }

        printf("%d ", i + 1); // line numbers
        for (int j = 0; j < 9; j++) {
            entry value = gameBoard[i][j];
            if (j % 3 == 0) {
                printf("|");
            }
            if (value.value == 0) {
                printf(" ");
            } else if (value.generatedInput) {
                // generierter wert, andere farbe notwendig
                printf("%s%d%s", KBLU, value.value, KNRM);
            } else {
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
int printMenu() {
    int inputValue;
    do {
        printf("Menu:\n");
        printf("1 -> undo\n");
        printf("2 -> Regelpruefung aktivieren\n");
        printf("3 -> Regelpruefung deaktivieren\n");
        printf("4 -> Loesung ausgeben\n");
        printf("5 -> menu schliessen\n");
        printf("9 -> Spiel beenden\n");
        scanf(" %1d", &inputValue);
    } while (!(inputValue > 0 && inputValue <= 5 || inputValue == 9));
    return inputValue;
}
