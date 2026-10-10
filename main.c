#include <stdio.h>

void initializeBoard(char board[3][3]) {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

void printBoard(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkWin(char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0;
}

int checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // If any cell still contains a number instead of X or O, game is not a draw yet
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;
            }
        }
    }
    return 1; // Board is full, it's a draw
}

int main() {
    char board[3][3];
    int choice;
    char currentPlayer = 'X';
    int gameOver = 0;

    initializeBoard(board);

    printf("Welcome to Tic Tac Toe!\n");
    printf("Enter a number from 1 to 9 corresponding to the grid position.\n");

    while (!gameOver) {
        printBoard(board);
        printf("Player %c's turn. Enter position (1-9): ", currentPlayer);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        // Validate range
        if (choice < 1 || choice > 9) {
            printf("Invalid choice. Please choose a number between 1 and 9.\n");
            continue;
        }

        // Convert choice (1-9) to 3x3 array coordinates (row, col)
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Check if the spot is already taken
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("That spot is already taken. Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            gameOver = 1;
        } else if (checkDraw(board)) {
            printBoard(board);
            printf("The game is a draw!\n");
            gameOver = 1;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
