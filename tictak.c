#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char board[3][3];
char currentPlayer = 'X';

char player1[30], player2[30];
int score1 = 0, score2 = 0;

/* Colors */
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

void clearScreen() {
    system("cls || clear");
}

void initializeBoard() {
    char ch='1';

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            board[i][j]=ch++;
        }
    }

    currentPlayer='X';
}

void printScore() {

    printf(CYAN);
    printf("\n===== SCOREBOARD =====\n");
    printf("%s (X): %d\n",player1,score1);
    printf("%s (O): %d\n",player2,score2);
    printf("======================\n");
    printf(RESET);
}

void displayBoard() {

    clearScreen();

    printf(YELLOW);
    printf("\n===== TIC TAC TOE =====\n");
    printf(RESET);

    printScore();

    printf("\n");
    printf("     %c | %c | %c\n",board[0][0],board[0][1],board[0][2]);
    printf("    ---|---|---\n");
    printf("     %c | %c | %c\n",board[1][0],board[1][1],board[1][2]);
    printf("    ---|---|---\n");
    printf("     %c | %c | %c\n",board[2][0],board[2][1],board[2][2]);
    printf("\n");
}

int checkWin() {

    for(int i=0;i<3;i++) {

        if(board[i][0]==board[i][1] &&
           board[i][1]==board[i][2])
            return 1;

        if(board[0][i]==board[1][i] &&
           board[1][i]==board[2][i])
            return 1;
    }

    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2])
        return 1;

    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0])
        return 1;

    return 0;
}

int checkDraw() {

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {

            if(board[i][j] != 'X' &&
               board[i][j] != 'O')
                return 0;
        }
    }

    return 1;
}

void updateScore(char winner) {

    if(winner=='X')
        score1++;
    else
        score2++;
}

void printWinner(char winner) {

    printf(GREEN);

    printf("\n===== GAME OVER =====\n");

    if(winner=='X')
        printf("Winner: %s\n",player1);
    else
        printf("Winner: %s\n",player2);

    printf("=====================\n");

    printf(RESET);
}

void playerMove() {

    int choice,row,col;

    printf(GREEN);
    printf("%s (%c) turn -> Enter position (1-9): ",
           currentPlayer=='X'?player1:player2,
           currentPlayer);

    printf(RESET);

    scanf("%d",&choice);

    row=(choice-1)/3;
    col=(choice-1)%3;

    if(choice<1 || choice>9 ||
       board[row][col]=='X' ||
       board[row][col]=='O') {

        printf(RED);
        printf("Invalid move! Try again.\n");
        printf(RESET);

        playerMove();
        return;
    }

    board[row][col]=currentPlayer;

    currentPlayer=
    (currentPlayer=='X') ? 'O':'X';
}

void playGame() {

    initializeBoard();

    while(1) {

        displayBoard();

        playerMove();

        if(checkWin()) {

            displayBoard();

            char win=
            (currentPlayer=='X') ? 'O':'X';

            updateScore(win);

            printWinner(win);

            break;
        }

        if(checkDraw()) {

            displayBoard();

            printf(YELLOW);
            printf("\n===== GAME OVER =====\n");
            printf("Match Draw\n");
            printf("=====================\n");
            printf(RESET);

            break;
        }
    }
}

int main() {

    int choice;

    printf(YELLOW);
    printf("===== WELCOME TO TIC TAC TOE =====\n");
    printf(RESET);

    printf("Enter Player 1 name (X): ");
    scanf("%s",player1);

    printf("Enter Player 2 name (O): ");
    scanf("%s",player2);

    while(1) {

        playGame();

        printf("\nDo you want to play again?\n");
        printf("1. Yes\n");
        printf("2. No\n");

        scanf("%d",&choice);

        if(choice!=1) {

            printf(CYAN);
            printf("\nThanks for playing!\n");
            printf(RESET);

            break;
        }
    }

    return 0;
}