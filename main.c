#include <stdio.h>

void printField(char name[]){
    printf("Spieler: %s\n", name);
    printf("  abc def ghi\n");

    for(int i = 0; i < 9; i++){
        if(i%3==0){
            printf("  --- --- --- \n");
        }
        printf("%d|   |   |   |\n", i+1);
    }
    printf("  --- --- --- \n");

}

int main(int argc, char** argv) {
    printf("Bitte namen eingeben: ");
    char line[256];
    scanf("%255[^\n]", line);
    printField(line);
    return 0;
}
