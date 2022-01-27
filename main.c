#include <stdio.h>

int gameBoard[9][9];
char playerName[256];

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

/*
 * save user inputted coordinate/value
 */
void saveValue(int x, int y, int value){
    gameBoard[x][y] = value;
}

int main(int argc, char** argv) {
    initGameBoard();
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
