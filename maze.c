#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//sa se genereze toate nr de tel care incep cu ceva (ex 0722) si sa se extraga din acea lista nr a caror cifra ponderata e maxima (de ex); sau ultimele 3 cifre sa fie divizibile cu 3
char **maze;
int num_lines = 0, num_cols = 0;

void maze_initialize(FILE *inputFile) {
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (ch == '\n') {
            num_lines++;
            if (num_cols == 0) {
                num_cols = ftell(inputFile) - (num_lines - 1);
            }
        }
    }

    fseek(inputFile, 0, SEEK_SET);

    maze = (char **)malloc(num_lines * sizeof(char *));
    if (maze == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_lines; i++) {
        maze[i] = (char *)malloc(num_cols * sizeof(char));
        if (maze[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_lines; i++) {
        fgets(maze[i], num_cols + 1, inputFile);
    }
}

void print_maze(FILE *outputFile) {
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_cols; j++) {
            fputc(maze[i][j], outputFile);
        }
        fputc('\n', outputFile);
    }
}

int cnt, steps;

void move(int lin, int col, FILE *f) {
    if (lin < 0 || lin >= num_lines || col < 0 || col >= num_cols) {
        return;
    }

    if (maze[lin][col] == 'E') {
        printf("End point at: [%d, %d]\n", lin, col);
        print_maze(f);
		
        cnt++;
    }

    if (maze[lin][col] != ' ' && maze[lin][col] != 'S') {
        return;
    }
	if (maze[lin][col] == '.') {
        return; // Already visited this position
    }

    maze[lin][col] = '.';
	steps++;

    move(lin, col - 1,f); 
    move(lin, col + 1,f); 
    move(lin - 1, col,f);
    move(lin + 1, col,f); 

    maze[lin][col] = ' ';
	steps--;
}




int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        exit(EXIT_FAILURE);
    }
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        exit(EXIT_FAILURE);
    }
    maze_initialize(inputFile);

    printf("Number of lines: %d, Number of columns: %d\n", num_lines, num_cols);

    char line[num_cols];
    int start_line = -1, start_col = -1;
    int end_line = -1, end_col = -1;
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (maze[i][j] == 'S') {
                start_line = i;
                start_col = j;
                printf("Start point found at: [%d, %d]\n", start_line, start_col);
            } else if (maze[i][j] == 'E') {
                end_line = i;
                end_col = j;
                printf("End point found at: [%d, %d]\n", end_line, end_col);
            }
        }
    }

    if (start_line == -1 || start_col == -1 || end_line == -1 || end_col == -1) {
        printf("Start or end point not found!\n");
        exit(EXIT_FAILURE);
    }

    move(start_line, start_col,outputFile);

	printf("Nr of sols: %d;\nSteps:%d\n",cnt,steps);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
