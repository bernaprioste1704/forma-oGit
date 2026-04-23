#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void loadingAnimation() {
    const int total_frames = 20;
    const char* animation[] = {"-", "\\", "|", "/"};
    for (int i = 0; i <= total_frames; ++i) {
        printf("\rCarregando %s ", animation[i % 4]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n");
}

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void playerMove() {
    int row, col;
    while (1) {
        printf("Sua vez (linha e coluna): ");
        if (scanf("%d %d", &row, &col) != 2 || row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("Movimento inválido. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else {
            board[row - 1][col - 1] = 'X';
            break;
        }
    }
}

void computerMove() {
    int row, col;
    srand(time(0));
    if (isBoardFull()) return;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    board[row][col] = 'O';
}

int main() {
    loadingAnimation();
    initializeBoard();
    int currentPlayer = 0; // 0 for player, 1 for computer

    while (1) {
        printBoard();
        if (currentPlayer == 0) {
            playerMove();
        } else {
            printf("Vez do computador...\n");
            computerMove();
        }

        if (checkWin()) {
            printBoard();
            if (currentPlayer == 0) {
                printf("Você venceu!\n");
            } else {
                printf("O computador venceu!\n");
            }
            break;
        }

        if (isBoardFull()) {
            printBoard();
            printf("Empate!\n");
            break;
        }

        currentPlayer = (currentPlayer + 1) % 2;
    }

    return 0;
}
