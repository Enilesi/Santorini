#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROWS 4
#define COLUMNS 5
#define DICE_NR 5
#define NUM_ROUNDS 2
#define NUM_PUBLIC_GOALS 10
#define NUM_SELECTED_PUBLIC_GOALS 3

// Define the structure for the player window
typedef struct {
    int gems[ROWS][COLUMNS];   // 2D array to store gems
    char private_goal;           // Integer for private goal
    char public_goals[NUM_SELECTED_PUBLIC_GOALS][100];  // Array to store public goals
} PlayerWindow;

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    NUM_COLORS // Number of colors
} Color;

typedef struct {
    int number;
    Color color;
} Die;

// Function to convert color enum value to string
const char *colorToString(Color colors) {
    switch (colors) {
        case RED:
            return "R";
        case GREEN:
            return "G";
        case BLUE:
            return "B";
        case YELLOW:
            return "Y";
        case PURPLE:
            return "P";
        default:
            return "U";
    }
}

// Function to throw five dice
void throwDice(Die *dice) {
    srand(time(NULL));

    for (int i = 0; i < DICE_NR; i++) {
        dice[i].number = (rand() % 5) + 1;
        dice[i].color = (Color)(rand() % NUM_COLORS);
    }
}

// Function to add a die to the board
void addDie(PlayerWindow *board, int row, int col, Die die) {
    board->gems[row][col] = die.number;
    board->gems[row][col] += (int)die.color * 1000;
}

// Function to print the board with added dice
void printBoard(PlayerWindow *board) {
    printf("Board with added dice:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int number = board->gems[i][j];
            Color color = (Color)(number / 1000); //tre sa intreb
            int value = number % 1000;
            if(value != 0)
                printf("%d:%s\t", value, colorToString(color));
            else
                printf("0:U\t");
        }
        printf("\n");
    }
}

// Function to read public goals from a file and select 3 randomly
void readAndSelectPublicGoals(char selectedGoals[NUM_SELECTED_PUBLIC_GOALS][100]) {
    FILE *file = fopen("public_goals.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char goals[NUM_PUBLIC_GOALS][100];
    int numGoals = 0;

    // Read all public goals from the file
    while (fgets(goals[numGoals], sizeof(goals[numGoals]), file) && numGoals < NUM_PUBLIC_GOALS) {
        numGoals++;
    }

    fclose(file);

    // Select 3 random public goals
    for (int i = 0; i < NUM_SELECTED_PUBLIC_GOALS; i++) {
        int randomIndex = rand() % numGoals;
        strcpy(selectedGoals[i], goals[randomIndex]);
    }
}

int main() {
    // Create instances of the PlayerWindow structure for both players
    PlayerWindow player1, player2;
    srand(time(NULL));

    // Initialize gems array for both players
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            player1.gems[i][j] = 0;  
            player2.gems[i][j] = 0;  
        }
    }

    // Set private goals for both players
    player1.private_goal = rand() % 4;
    player2.private_goal = rand() % 4;

    // Set public goals for both players
    char selectedGoals[NUM_SELECTED_PUBLIC_GOALS][100];
    readAndSelectPublicGoals(selectedGoals);

    // Assign public goals to both players
    for (int i = 0; i < NUM_SELECTED_PUBLIC_GOALS; i++) {
        strcpy(player1.public_goals[i], selectedGoals[i]);
        strcpy(player2.public_goals[i], selectedGoals[i]);
    }

    // Print information for both players
    printf("Player 1 Window:\n");
    printf("Private Goal: ");
    switch (player1.private_goal) {
        case 0:
            printf("Red\n");
            break;
        case 1:
            printf("Green\n");
            break;
        case 2:
            printf("Blue\n");
            break;
        case 3:
            printf("Purple\n");
            break;
        case 4:
            printf("Yellow\n");
            break;
    }
    printf("Public Goals:\n%s\n%s\n%s\n", player1.public_goals[0], player1.public_goals[1], player1.public_goals[2]);

    printf("\nPlayer 2 Window:\n");
    printf("Private Goal: ");
    switch (player2.private_goal) {
        case 0:
            printf("Red\n");
            break;
        case 1:
            printf("Green\n");
            break;
        case 2:
            printf("Blue\n");
            break;
        case 3:
            printf("Purple\n");
            break;
        case 4:
            printf("Yellow\n");
            break;
    }
    printf("Public Goals:\n%s\n%s\n%s\n", player2.public_goals[0], player2.public_goals[1], player2.public_goals[2]);

    // Loop for multiple rounds
    for (int round = 1; round <= NUM_ROUNDS; round++) {
        printf("\nRound %d\n", round);

        // Throw five dice for each round
        Die dice[DICE_NR];
        throwDice(dice);

        // Print the results for the current round
        printf("\nResults of the dice:\n");
        for (int i = 0; i < DICE_NR; i++) {
            printf("Die %d: Number: %d, Color: %s\n", i + 1, dice[i].number, colorToString(dice[i].color));
        }

        // Ask the users to choose where to place each die alternatively for both players
        printf("\nEnter the die number (1-5), row, and column(with a whitespace between them)for each die (0-3 for row, 0-4 for column) alternately for Player 1 and Player 2:\n");
        for (int i = 0; i < DICE_NR-3; i++) {
            int dieNum, row, col;

            // Player 1's turn
            printf("Player 1's turn: Enter die number, row, and column for the chosen die: ");
            scanf("%d %d %d", &dieNum, &row, &col);
            addDie(&player1, row, col, dice[dieNum - 1]);

            // Player 2's turn
            printf("Player 2's turn: Enter die number, row, and column for the chosen die: ");
            scanf("%d %d %d", &dieNum, &row, &col);
            addDie(&player2, row, col, dice[dieNum - 1]);
        }

        // Print the board with added dice for both players
        printf("\nPlayer 1's Board:\n");
        printBoard(&player1);

        printf("\nPlayer 2's Board:\n");
        printBoard(&player2);
    }

        return 0;
    }