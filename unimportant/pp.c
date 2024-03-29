#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 8

// Structure to represent a piece
typedef struct {
    char symbol; // Symbol representing the piece
    bool isWhite; // Flag to indicate if the piece is white (true) or black (false)
} Piece;

// Structure to represent the chess board
typedef struct {
    Piece squares[BOARD_SIZE][BOARD_SIZE]; // Array representing the board squares
} Board;

// Function to initialize the chess board
void initializeBoard(Board *board) {
    // Set up the initial configuration of the board
    // For simplicity, we'll only set up the initial positions of pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        board->squares[1][i].symbol = 'P'; // Pawn
        board->squares[1][i].isWhite = false; // Black pawn

        board->squares[6][i].symbol = 'P'; // Pawn
        board->squares[6][i].isWhite = true; // White pawn
    }

    // Set up other initial positions (rooks, knights, bishops, kings, and queens) as needed
    // For simplicity, we'll skip these for now
}

// Function to print the chess board
void printBoard(Board *board) {
    printf("\n  a b c d e f g h\n"); // Print column letters
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", BOARD_SIZE - i); // Print row numbers
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->squares[i][j].symbol == '\0') {
                printf(". "); // Empty square
            } else {
                printf("%c ", board->squares[i][j].symbol); // Print piece symbol
            }
        }
        printf("%d\n", BOARD_SIZE - i); // Print row numbers
    }
    printf("  a b c d e f g h\n"); // Print column letters
}

int main() {
    Board board;

    // Initialize the chess board
    initializeBoard(&board);

    // Print the initial board state
    printBoard(&board);

    return 0;
}
