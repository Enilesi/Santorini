#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>  //for strch
#include <unistd.h> // for printing with delay
#define BOARD_SIZE 5

#define MAX_DOMES 18

#define PINK_HIGHLIGHT "\033[48;2;255;64;163m"
#define BLUE_HIGHLIGHT "\033[48;2;0;158;254m"
#define GREEN_HIGHLIGHT "\033[48;2;0;204;0m"
#define HIGHLIGHT_RESET "\033[m"

#define BACKGROUND "\033[48;2;234;182;224m"

#define PINK "\033[38;2;255;64;163m"
#define BLUE "\033[38;2;0;158;254m"
#define GREEN "\033[38;2;0;204;0m"
#define GOLD "\033[38;2;218;165;32m"
#define PURPLE "\033[38;2;190;64;240m"
#define LILA "\033[38;2;240;134;255m"
#define RED "\033[38;2;247;106;106m"

#define RESET "\033[m"

#define ROWS 4
#define COLUMNS 8
#define LEN_CASES 15

// i must do a function to check if no more moves and if so=>
typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    Position position;
    char color;
    char gender;
} Worker;

typedef struct
{
    Worker worker[2];
    char name[50]; // i shall do a function to verify if players have the same name, and if so, i must add an index
} Player;

typedef struct
{
    Position position;
} Dome;

Player player[4];
int board[BOARD_SIZE][BOARD_SIZE];
int numPlayers, nr_workers;
int level1, level2, level3, domes;
Dome dome[MAX_DOMES];

void err(char *message)
{
    printf("%s", message);
    exit(1);
}

void initialize_domes()
{
    int i;
    for (i = 0; i < MAX_DOMES; i++)
    {
        dome[i].position.x = -1;
        dome[i].position.y = -1;
    }
}

void init_4_players(int i)
{
    printf(LILA "Enter gender of %s's worker:\n G-girl\n B-boy\n" RESET, player[i].name);

    if (scanf(" %c", &player[i].worker[0].gender) != 1)
    {
        err(RED "Error reading worker's gender" RESET);
    }

    if ((i == 1 || i == 3) && player[i].worker[0].gender == player[i - 1].worker[0].gender)
    {
        err("Invalid choice. Two teammates can't have the same gender for a worker");
    }

    printf("Enter the color of %s's worker:\n ->P-pink " PINK_HIGHLIGHT " " HIGHLIGHT_RESET "\n ->G-green " GREEN_HIGHLIGHT " " HIGHLIGHT_RESET "\n ->B-blue " BLUE_HIGHLIGHT " " HIGHLIGHT_RESET "\n \n", player[i].name);

    if (scanf(" %c", &player[i].worker[0].color) != 1)
    {
        err(RED "Error reading worker's color" RESET);
    }

    if (player[i].worker[0].color != 'P' && player[i].worker[0].color != 'G' && player[i].worker[0].color != 'B')
    {
        err(RED "Invalid choice. Worker's color must be 'B', 'P', or 'G'" RESET);
    }

    if ((i == 1 || i == 3) && player[i].worker[0].color != player[i - 1].worker[0].color)
    {
        err(RED "Invalid choice. Two teammates must have the same color for their workers" RESET);
    }
}

void init_not_4_players(int i)
{
    player[i].worker[0].gender = 'G';
    player[i].worker[1].gender = 'B';

    int ok = 1;
    while (ok == 1)
    {
        int cond = 1;
        printf(LILA "\nEnter the color of %s's worker:\n" RESET " ⟶ P: pink " PINK_HIGHLIGHT " " HIGHLIGHT_RESET "\n ⟶ G: green " GREEN_HIGHLIGHT " " HIGHLIGHT_RESET "\n ⟶ B: blue " BLUE_HIGHLIGHT " " HIGHLIGHT_RESET "\n \n", player[i].name);
        scanf(" %c", &player[i].worker[0].color);
        if (player[i].worker[0].color != 'P' && player[i].worker[0].color != 'B' && player[i].worker[0].color != 'G')
        {
            printf(RED "Invalid color given. Try again!\n" RESET);
            cond = 0;
        }
        else if (i > 0)
        {
            for (int j = i - 1; j >= 0; j--)
                if (player[i].worker[0].color == player[j].worker[0].color)
                {
                    printf(RED "Invalid color given. Two different players can't share a color!\n" RESET);
                    cond = 0;
                }
        }
        if (cond == 1)
            ok = 0;
    }
    player[i].worker[1].color = player[i].worker[0].color;
}

void print_header(char text[])
{
    char text_copy[256];
    strncpy(text_copy, text, sizeof(text_copy) - 1);
    text_copy[sizeof(text_copy) - 1] = '\0';

    char *word = strtok(text_copy, " \n");
    int colorIndex = 0;

    while (word != NULL)
    {
        switch (colorIndex % 3)
        {
        case 0:
            printf(PINK "%s " RESET, word);
            break;
        case 1:
            printf(BLUE "%s " RESET, word);
            break;
        case 2:
            printf(GREEN "%s " RESET, word);
            break;
        }
        word = strtok(NULL, " \n");
        colorIndex++;
    }
    printf("\n");
}

void initialize_game()
{
    // printf("\033[45m");
    print_header("LET'S START THE GAME!\n");
    printf(LILA "\n\nEnter the number of players:\n" RESET);
    if (scanf("%d", &numPlayers) != 1)
    {
        err(RED "Error reading number of players" RESET);
    }
    if (numPlayers < 2 || numPlayers > 4)
    {
        err(RED "Invalid. Number of players must be between 2 and 4. Exiting.\n" RESET);
    }
    if (numPlayers == 4)
        nr_workers = 1;
    else
        nr_workers = 2;
    for (int i = 0; i < numPlayers; i++)
    {
        if (numPlayers == 4)
        {
            if (i == 0)
            {
                printf("\n");
                print_header("\n\n>>ENTER FIRST TEAM:\n");
            }
            else if (i == 2)
            {
                printf("\n");
                print_header("\n\n>>ENTER SECOND TEAM:\n");
            }
        }
        switch (i)
        {
        case 0:
            printf(LILA "\nEnter the name for first player:\n" RESET);
            break;
        case 1:
            printf(LILA "\nEnter the name for second player:\n" RESET);
            break;
        case 2:
            printf(LILA "\nEnter the name for third player:\n" RESET);
            break;
        case 3:
            printf(LILA "\nEnter the name for fourth player:\n" RESET);
            break;

        default:
            break;
        }
        scanf("%s", player[i].name);

        if (numPlayers == 4)
            init_4_players(i);
        else
            init_not_4_players(i);
        player[i].worker[0].position.x = -1;
        player[i].worker[0].position.y = -1;
        player[i].worker[1].position.x = -1;
        player[i].worker[1].position.y = -1;
    }
    initialize_domes();
}

int is_worker_on_the_position(int x, int y)
{
    for (int k = 0; k < numPlayers; k++)
        for (int l = 0; l < 2; l++)
            if (player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                return 1;
    return 0;
}

void print_worker(int x, int y)
{
    for (int k = 0; k < numPlayers; k++)
        for (int l = 0; l < nr_workers; l++)
        {
            if (player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
            {
                switch (player[k].worker[l].color)
                {
                case 'G':
                    printf("\033[0;37;40m %c%d \033[0m", player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                    break;
                case 'W':
                    printf("\033[0;30;47m %c%d \033[0m", player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                    break;
                case 'B':
                    printf("\033[0;37;44m %c%d \033[0m", player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                    break;
                default:
                    printf("N");
                    break;
                }
            }
        }
}
void print_legend()
{
    printf("Map:\n");
    for (int i = 0; i < numPlayers; i++)
    {
        if (player[i].name)
        {
            printf("%10s:", player[i].name);
            for (int j = 0; j < nr_workers; j++)
            {
                if (player[i].worker[j].color)
                {
                    switch (player[i].worker[j].color)
                    {
                    case 'P':
                        printf(PINK_HIGHLIGHT " %c%d " HIGHLIGHT_RESET, player[i].worker[j].gender, j + 1); /// l for B1 B2 G1 G2
                        break;
                    case 'B':
                        printf(BLUE_HIGHLIGHT " %c%d " HIGHLIGHT_RESET, player[i].worker[j].gender, j + 1); /// l for B1 B2 G1 G2
                        break;
                    case 'G':
                        printf(GREEN_HIGHLIGHT " %c%d " HIGHLIGHT_RESET, player[i].worker[j].gender, j + 1); /// l for B1 B2 G1 G2
                        break;
                    default:
                        printf("N");
                        break;
                    }
                }
            }
            printf("\n");
        }
    }

    printf("\n");
}
char cases_simple[ROWS][COLUMNS][LEN_CASES] = {
    {{"             "},
     {"             "},
     {"             "},
     {"             "},
     {"   __________"},
     {"  /         /"},
     {" /         / "},
     {"/_________/  "}},
    {{"             "},
     {"             "},
     {"             "},
     {"   _________ "},
     {"  /        /|"},
     {" /________/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"             "},
     {"             "},
     {"   ________  "},
     {"  /______ /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"             "},
     {"    ______   "},
     {"   /_____/|  "},
     {"  |__3__| /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}}};

char cases_dome[ROWS][COLUMNS][LEN_CASES] = {
    {{"             "},
     {"             "},
     {"             "},
     {"             "},
     {"   ___D_____ "},
     {"  / /__/|   /"},
     {" / |__|/   / "},
     {"/_________/  "}},
    {{"             "},
     {"             "},
     {"             "},
     {"   ___D_____ "},
     {"  / /__/|  /|"},
     {" /_|__|/__/ |"},
     {"|   1    | / "},
     {"|________|/  "}},
    {{"             "},
     {"     _D_     "},
     {"    /__/|__  "},
     {"  /_|__|/_/| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"      _D_    "},
     {"    _/__/|_  "},
     {"   /|__|//|  "},
     {"  |__3__| /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}}};

char cases_girl[ROWS][COLUMNS][LEN_CASES] = {
    {{"             "},
     {"             "},
     {"             "},
     {"             "},
     {"   __*0*_____"},
     {"  /  /|\\    /"},
     {" /   / \\   / "},
     {"/_________/  "}},
    {{"             "},
     {"             "},
     {"     *0*     "},
     {"   __/|\\____ "},
     {"  /  / \\   /|"},
     {" /________/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"             "},
     {"     *0*     "},
     {"   __/|\\___  "},
     {"  /__/_\\_ /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"     *0*     "},
     {"    _/|\\__   "},
     {"   /_/_\\_/|  "},
     {"  |__3__| /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}}};

char cases_boy[ROWS][COLUMNS][LEN_CASES] = {
    {{"             "},
     {"             "},
     {"             "},
     {"             "},
     {"   ___0______"},
     {"  /  /|\\    /"},
     {" /   / \\   / "},
     {"/_________/  "}},
    {{"             "},
     {"             "},
     {"      0      "},
     {"   __/|\\____ "},
     {"  /  / \\   /|"},
     {" /________/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"             "},
     {"      0      "},
     {"   __/|\\___  "},
     {"  /__/_\\_ /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}},
    {{"      0      "},
     {"    _/|\\__   "},
     {"   /_/_\\_/|  "},
     {"  |__3__| /| "},
     {" |   2   | /|"},
     {" |_______|/ |"},
     {"|    1    | /"},
     {"|_________|/ "}}};

int search_player_worker_pos(int x, int y)
{
    for (int k = 0; k < numPlayers; k++)
        for (int l = 0; l < 2; l++)
            if (player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                return k;
    return -1;
}
int search_worker_pos(int x, int y)
{
    for (int k = 0; k < numPlayers; k++)
        for (int l = 0; l < 2; l++)
            if (player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                return l;
    return -1;
}

void indented_space(int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf(" ");
    }
}

int check_if_exists_dome_on_that_pos(int x, int y)
{
    for (int i = 0; i < domes; i++) // changed from max domes
        if (dome[i].position.x == x && dome[i].position.y == y && dome[i].position.x != -1)
            return 1;
    return 0;
}
void print_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int k = 0; k < COLUMNS; k++)
        {
            indented_space(5 * (BOARD_SIZE - i)); // or 10
            for (int j = 0; j < BOARD_SIZE; j++)
            {

                int index_i = search_player_worker_pos(i, j);
                int index_j = search_worker_pos(i, j);
                if (index_i != -1 && index_j != -1)
                {
                    switch (player[index_i].worker[index_j].gender)
                    {
                    case 'B':
                        switch (player[index_i].worker[index_j].color)
                        {
                        case 'G':
                            printf(GREEN "%s      " RESET, cases_boy[board[i][j]][k]);
                            break;
                        case 'P':
                            printf(PINK "%s      " RESET, cases_boy[board[i][j]][k]);
                            break;
                        case 'B':
                            printf(BLUE "%s      " RESET, cases_boy[board[i][j]][k]);
                            break;

                        default:
                            break;
                        }
                        break;
                    case 'G':
                        switch (player[index_i].worker[index_j].color)
                        {
                        case 'G':
                            printf(GREEN "%s      " RESET, cases_girl[board[i][j]][k]);
                            break;
                        case 'P':
                            printf(PINK "%s      " RESET, cases_girl[board[i][j]][k]);
                            break;
                        case 'B':
                            printf(BLUE "%s      " RESET, cases_girl[board[i][j]][k]);
                            break;

                        default:
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (check_if_exists_dome_on_that_pos(i, j))
                {
                    printf("%s      ", cases_dome[board[i][j]][k]);
                }
                else
                {
                    printf("%s      ", cases_simple[board[i][j]][k]);
                }
            }
            if (k == 6)
                printf("%d", i);
            printf("\n");
        }
        printf("\n");
    }
    printf("\t  %d\t", 0);
    printf("\t     %d\t", 1);
    printf("\t        %d\t", 2);
    printf("\t   %d\t", 3);
    printf("\t      %d\t", 4);

    printf("\n");
    print_legend();
}

int is_valid_move(int x, int y, int index_i, int index_j)
{

    if (check_if_exists_dome_on_that_pos(x, y) == 1)
        return 0;

    if (board[x][y] == 4)
        return 0; // if dome

    if ((x < 0 || y < 0) || ((x >= BOARD_SIZE || y >= BOARD_SIZE)))
        return 0;
    for (int i = 0; i < numPlayers; i++)
    {
        if ((player[i].worker[0].position.x == x && player[i].worker[0].position.y == y) || (player[i].worker[1].position.x == x && player[i].worker[1].position.y == y) && index_i != i)
            return 0;
    }
    if (board[x][y] > board[player[index_i].worker[index_j].position.x][player[index_i].worker[index_j].position.y])
    {
        if (board[x][y] - board[player[index_i].worker[index_j].position.x][player[index_i].worker[index_j].position.y] > 1)
            return 0;
        else
            return 1;
    }
    else
        return 1;
    return 1;
}

void win(int i)
{
    if (numPlayers != 4)
    {
        print_board();
        print_header("THE GAME IS OVER!");
        printf(LILA "\n\n%s won the chalenge\n" RESET, player[i].name);
        exit(0);
    }
    else
    {
        if (i < 2)
        {
            print_board();
            print_header("THE GAME IS OVER!");
            printf(LILA " \nThe first team composed of %s and %s won the chalenge\n" RESET, player[0].name, player[1].name);
            exit(0);
        }
        else
        {
            print_board();
            print_header("THE GAME IS OVER!");
            printf(LILA " \nThe second team composed of %s and %s won the chalenge\n" RESET, player[2].name, player[3].name);
            exit(0);
        }
    }
}

int building_in_the_corners(int x, int y, int i, int l)
{

    if (x == 0 && y == 0)
    {
        if ((player[i].worker[l].position.x == 0 && player[i].worker[l].position.y == 1) ||
            (player[i].worker[l].position.x == 1 && player[i].worker[l].position.y == 1) ||
            (player[i].worker[l].position.x == 1 && player[i].worker[l].position.y == 0))
            return 1;
    }
    else if (x == 4 && y == 0)
    {
        if ((player[i].worker[l].position.x == 3 && player[i].worker[l].position.y == 0) ||
            (player[i].worker[l].position.x == 3 && player[i].worker[l].position.y == 1) ||
            (player[i].worker[l].position.x == 4 && player[i].worker[l].position.y == 1))
            return 1;
    }
    else if (x == 0 && y == 4)
    {
        if ((player[i].worker[l].position.x == 0 && player[i].worker[l].position.y == 3) ||
            (player[i].worker[l].position.x == 1 && player[i].worker[l].position.y == 3) ||
            (player[i].worker[l].position.x == 1 && player[i].worker[l].position.y == 4))
            return 1;
    }
    else if (x == 0 && y == 4)
    {
        if ((player[i].worker[l].position.x == 3 && player[i].worker[l].position.y == 4) ||
            (player[i].worker[l].position.x == 3 && player[i].worker[l].position.y == 3) ||
            (player[i].worker[l].position.x == 4 && player[i].worker[l].position.y == 3))
            return 1;
    }
    return 0;
}

int is_building_in_the_boder(int x, int y, int i, int l)
{
    if (building_in_the_corners(x, y, i, l) == 1)
        return 1;
    else
    {
        if (y == 0)
        {
            if ((player[i].worker[l].position.x == x - 1 && player[i].worker[l].position.y == y) ||
                (player[i].worker[l].position.x == x && player[i].worker[l].position.y == y + 1) ||
                (player[i].worker[l].position.x == x + 1 && player[i].worker[l].position.y == y) ||
                (player[i].worker[l].position.x == x - 1 && player[i].worker[l].position.y == y + 1) ||
                (player[i].worker[l].position.x == x + 1 && player[i].worker[l].position.y == y + 1))
                return 1;
        }
        else if (y == 4)
        {
            if ((player[i].worker[l].position.x == x - 1 && player[i].worker[l].position.y == y) ||
                (player[i].worker[l].position.x == x && player[i].worker[l].position.y == y - 1) ||
                (player[i].worker[l].position.x == x + 1 && player[i].worker[l].position.y == y) ||
                (player[i].worker[l].position.x == x - 1 && player[i].worker[l].position.y == y - 1) ||
                (player[i].worker[l].position.x == x + 1 && player[i].worker[l].position.y == y - 1))
                return 1;
        }
    }
    return 0;
}

int is_building_not_in_the_border(int x, int y, int i, int l)
{
    if (check_if_exists_dome_on_that_pos(x, y) == 1)
        return 0;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if ((x + dx >= 0 && x + dx < BOARD_SIZE) &&
                (y + dy >= 0 && y + dy < BOARD_SIZE) &&
                (dx != 0 || dy != 0) &&
                player[i].worker[l].position.x == x + dx &&
                player[i].worker[l].position.y == y + dy)
            {
                return 1;
            }
        }
    }
    return 0;
}

int is_valid_position_building(int x, int y, int i)
{
    if ((x > 4) || (x < 0) || (y > 4) || (y < 0))
        return 0;
    if (check_if_exists_dome_on_that_pos(x, y) == 1)
        return 0;

    for (int k = 0; k < 4; k++)
        for (int l = 0; l < 2; l++)
        {
            if (player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
            { // no building over worker
                return 0;
            }
        }
    if (player[i].worker[0].position.x == -1 && player[i].worker[1].position.x == -1) // if it's your first time ever building
        return 1;

    for (int l = 0; l < nr_workers; l++) // must verify if worker exists because i can have 4 players
    {
        if (is_building_in_the_boder(x, y, i, l) == 1 || is_building_not_in_the_border(x, y, i, l) == 1)
            return 1;
    }

    return 0;
}

int construct_building(int x, int y, int i)
{
    if (is_valid_position_building(x, y, i) == 1)
    {
        switch (board[x][y])
        {
        case 0:
            if (level1 <= 22)
            {
                board[x][y]++;
                level1++;
                return 1;
            }
        case 1:
            if (level2 <= 18)
            {
                board[x][y]++;
                level2++;
                return 1;
            }
        case 2:
            if (level3 <= 14)
            {
                board[x][y]++;
                level3++;
                return 1;
            }
        case 3:
            win(i);
            return 1;

        default:
            return 0;
        }
    }
    return 0;
}

int move_worker(int x, int y, int i, int j)
{
    if (board[x][y] == 3)
        win(i);
    if (is_valid_move(x, y, i, j))
    { // i must also implement an else
        player[i].worker[j].position.x = x;
        player[i].worker[j].position.y = y;
        return 1;
    }
    return 0;
}

int search_worker_index(int gender, int i)
{

    for (int l = 0; l < nr_workers; l++)
        if (player[i].worker[l].gender == gender)
            return l;
    return -1;
}
int check_if_exists_worker_ont_that_pos(int x, int y)
{
    for (int i = 0; i < numPlayers; i++)
    {
        for (int j = 0; j < nr_workers; j++)
            if (player[i].worker[j].position.x == x && player[i].worker[j].position.y == y)
                return 1;
    }
    return 0;
}
int construct_dome(int pos_x, int pos_y) // i shall check if worker on that position
{
    if (domes == 18)
    {
        printf(RED "Can't build domes anymore" RESET);
        return -1;
    }
    if (check_if_exists_worker_ont_that_pos(pos_x, pos_y) == 1)
        return 0;
    if (check_if_exists_dome_on_that_pos(pos_x, pos_y) == 0)
    {
        dome[domes].position.x = pos_x; /// or to 1, I shall think in the future
        dome[domes].position.y = pos_y;
        domes++;
        return 1;
    }
    return 0;
}

void print_atlas()
{
    // printf(GOLD);

    // printf("                                                            \n");
    // printf("                                                            \n");
    // printf("                           .::::.                          \n");
    // printf("                       .-===-::.:-===-                      \n");
    // printf("                     -=:  .   :   .  .==.                   \n");
    // printf("                   .+:   .    :    :   .-=                  \n");
    // printf("                  .+:...-.....=.....-...-:+                 \n");
    // printf("                  +..   :     -     :    .:=                \n");
    // printf("                 -*#+  ..     -     :    . *                \n");
    // printf("                 +@@=::-::::::=:::::=::::-:*                \n");
    // printf("                 :%%%% ..     -     :    .   *                \n");
    // printf("                 -@@@   :     -     :    .-:                \n");
    // printf("                 %%@@@:..-:....=--:.:-...:=-                 \n");
    // printf("                :@@@@=   :  =@%%%%#=:   :=+=                 \n");
    // printf("                +@@@%%*-. . =#@%%#: .-=*#@#                 \n");
    // printf("                .#@@##%%@#*===+%%@#+-=+=+#@@%%                 \n");
    // printf("                  .+%%@@@@@%%#%%%%%%#+=@@%%@@@+                 \n");
    // printf("                     :*%%@@@@@@@@#@@*@@@%%+.                  \n");
    // printf("                      .@@%%@@@@@@*@@@-.                      \n");
    // printf("                       .%%@#%%%%#*@@@=                        \n");
    // printf("                        =@@%%%%@@#-                          \n");
    // printf("                        =@@%%@%%%%                           \n");
    // printf("                       -*%%%%####*.                         \n");
    // printf("                       #*##%%@@##+*##-                      \n");
    // printf("                      .@%%@@@@@%%*%%@@%%*:                    \n");
    // printf("                      *@@@@@@@@%%*@@@@@#@=                   \n");
    // printf("                .    :#@@@@@@@#-##*%%@@@%%.                   \n");
    // printf("               =@@@@@@+@%%%%://     :@@@%%.                    \n");
    // printf(RESET);
}

int god_power(int i)
{
    int ok = 1;
    while (ok == 1)
    {
        print_header("--- A T L A S ---\n");
        printf(LILA "Do you want to use the God Power?\n" RESET);
        print_atlas();
        printf("Yes/No\n");
        char answear[4];
        scanf("%s", answear);
        if (strcmp(answear, "Yes") == 0)
        {
            ok = 0;
            return 1;
        }
        else if (strcmp(answear, "No") == 0)
        {
            ok = 0;
            return 0;
        }
        else
        {
            printf(RED "Invalid answear. Try again!" RESET);
        }
    }
}
int doming(int i)
{
    if (god_power(i) == 1)
    {
        int ok = 1;
        while (ok == 1)
        {
            printf(LILA "Give your coordinates for the dome (0->4) with the format:\nx y\n" RESET);
            int dome_x, dome_y;
            if (scanf("%d %d", &dome_x, &dome_y) == 2)
            {
                int answer = construct_dome(dome_x, dome_y);
                if (answer == 1)
                {
                    print_header("\nThe game looks now like this:\n");
                    print_board();
                    printf("\n");
                    ok = 0;
                    return 1;
                }
                else if (answer == 0)
                {
                    printf(RED "Invalid coordinates for the dome. Try again!" RESET);
                }
                else if (answer == -1)
                {
                    return 0;
                }
            }
            else
            {
                printf(RED "Invalid input format. Please enter two integers separated by a space!\n" RESET);
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
            }
        }
    }
    return 0;
}

void building(int i)
{
    print_header("\nLET'S BUILD!");
    printf("\nThe game looks like this:\n");
    print_board();

    if (doming(i) == 0)
    {
        int ok = 1;
        while (ok == 1)
        {
            printf(LILA "Give your coordinates for the building (0->4) with the format:\nx y\n" RESET);
            int building_x, building_y;
            if (scanf("%d %d", &building_x, &building_y) == 2)
            {
                if (construct_building(building_x, building_y, i) == 1)
                {
                    printf("\nThe game looks now like this:\n");
                    print_board();
                    printf("\n");
                    ok = 0;
                }
                else
                {
                    printf(RED "Invalid choice for the building. Try again!" RESET);
                }
            }
            else
            {
                printf(RED "Invalid choice for the building. Try again!" RESET);
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
            }
        }
    }
}

void moving(int i)
{
    print_header("\nLET'S MOVE!");
    printf("\nThe game looks like this:\n");
    print_board();

    int ok1 = 1;
    int worker_index;
    char gender;

    while (ok1 == 1)
    {
        printf(LILA "Give the gender of your worker, %s:\nB/G \n" RESET, player[i].name);

        if (scanf(" %c", &gender) == 1)
        {
            worker_index = search_worker_index(gender, i);
            if (worker_index == -1)
            {
                printf(RED "Invalid choice. Choose an existing worker!\n" RESET);
            }
            else
            {
                ok1 = 0;
            }
        }
        else
        {
            printf(RED "Invalid choice. Choose an existing worker!\n" RESET);
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }
    }

    int ok2 = 1;
    while (ok2 == 1)
    {
        printf(LILA "Give the coordinates for your worker (0->4),%s, with the format:\nx y\n" RESET, player[i].name);
        int worker_x, worker_y;
        if (scanf(" %d %d", &worker_x, &worker_y) == 2)
        {
            if (move_worker(worker_x, worker_y, i, worker_index) == 1)
            {
                printf("\nThe game looks now like this:\n");
                print_board();
                printf("\n");
                ok2 = 0;
            }
            else
            {
                printf(RED "Invalid choice. Choose another set of coordinates for the worker!\n" RESET);
            }
        }
        else
        {
            printf(RED "Invalid choice. Choose another set of coordinates for the worker!\n" RESET);
            // Clear the input buffer
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }
    }
}

int surounded_by_buildings_and_domes(int x, int y)
{
    int count = 0;
    for (int j = 0; j < domes; j++)
    {
        for (int dx = -1; dx <= 1; dx++) // no free space from buildings and domes
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if ((x + dx >= 0 && x + dx < BOARD_SIZE) &&
                    (y + dy >= 0 && y + dy < BOARD_SIZE) &&
                    (dx != 0 || dy != 0))
                {
                    if (dome[j].position.x == x + dx && dome[j].position.y == y + dy)
                        count++;
                    else
                    {
                        switch (board[x + dx][x + dy])
                        {
                        case 0:
                            if (level1 + 1 > 22)
                                count++;
                            break;
                        case 1:
                            if (level2 + 1 > 18)
                                count++;
                            break;
                        case 2:
                            if (level3 + 1 > 14)
                                count++;
                            break;
                        case 3:
                            if (domes + 1 > MAX_DOMES)
                                count++;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
    return count;
}

int surounded_by_other_workers(int i, int x, int y)
{
    int count = 0;

    for (int j = 0; j < numPlayers; j++)
        for (int l = 0; l < nr_workers; l++)
        {

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if ((x + dx >= 0 && x + dx < BOARD_SIZE) &&
                        (y + dy >= 0 && y + dy < BOARD_SIZE) &&
                        (dx != 0 || dy != 0) &&
                        (player[j].worker[l].position.x == x + dx && player[j].worker[l].position.y == y + dy) &&
                        (player[j].worker[l].position.x != player[i].worker[l].position.x &&
                         player[j].worker[l].position.y != player[i].worker[l].position.y))
                        count++;
                }
            }
        }
    return count;
}

int cant_build_anymore(int i)
{

    int count1 = surounded_by_buildings_and_domes(player[i].worker[0].position.x, player[i].worker[0].position.y) + surounded_by_other_workers(i, player[i].worker[0].position.x, player[i].worker[0].position.y);
    int count2 = 0;
    if (numPlayers < 4)
        count2 = surounded_by_buildings_and_domes(player[i].worker[1].position.x, player[i].worker[1].position.y) + surounded_by_other_workers(i, player[i].worker[1].position.x, player[i].worker[1].position.y);
    if (count1 >= 8 && count2 >= 8)
        return 1;
    return 0;
}
int no_climbing_position(int x, int y)
{
    int count = 0;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if ((x + dx >= 0 && x + dx < BOARD_SIZE) &&
                (y + dy >= 0 && y + dy < BOARD_SIZE) &&
                (dx != 0 || dy != 0))
            {
                if ((board[x + dx][y + dy] - board[x][y] > 1) ||     // too high
                    is_worker_on_the_position(x + dx, y + dy) ||     // worker
                    check_if_exists_dome_on_that_pos(x + dx, y + dy) // dome
                )
                    count++;
            }
        }
    }
    return count;
}
int cant_climb_anymore(int i)
{

    int count1 = no_climbing_position(player[i].worker[0].position.x, player[i].worker[0].position.y);
    int count2 = 0;
    if (numPlayers < 4)
        count2 = no_climbing_position(player[i].worker[1].position.x, player[i].worker[1].position.y);
    if (count1 >= 8 && count2 >= 8)
        return 1;
    return 0;
}

void swapy_nr(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void swapy_char(char *a, char *b)
{
    char aux = *a;
    *a = *b;
    *b = aux;
}

void swapy_strings(char *a, char *b)
{
    char *aux;
    aux = strdup(a); // to alocate corectly
    strcpy(a, b);
    strcpy(b, aux);
    free(aux); // because, as i alocate, I need to free
}

void interchange_players(int i1, int i2)
{
    for (int l = 0; l < nr_workers; l++)
    {
        swapy_nr(&player[i1].worker[l].position.x, &player[i2].worker[l].position.x);
        swapy_nr(&player[i1].worker[l].position.y, &player[i2].worker[l].position.y);
        swapy_char(&player[i1].worker[l].color, &player[i2].worker[l].color);
        swapy_char(&player[i1].worker[l].gender, &player[i2].worker[l].gender);
    }
    swapy_strings(player[i1].name, player[i2].name);
}

void delete_player(int i)
{
    for (int j = i; j < numPlayers - 1; j++)
    {
        interchange_players(j, j + 1);
    }
    if (numPlayers == 3)
    {
        for (int l = 0; l < nr_workers; l++)
        {
            player[2].worker[l].position.x = -2;
            player[2].worker[l].position.y = -2;
            player[2].worker[l].gender = '\0';
            player[2].worker[l].color = '\0';
            player[2].name[0] = '\0';
        }
    }
    else
    {
        for (int l = 0; l < nr_workers; l++)
        {
            player[3].worker[l].position.x = -2;
            player[3].worker[l].position.y = -2;
            player[3].worker[l].gender = '\0';
            player[3].worker[l].color = '\0';
            player[3].name[0] = '\0';
        }
    }
    numPlayers--;
}

int no_more_moves(int i)
{
    if (cant_climb_anymore(i) == 1 || cant_build_anymore(i) == 1)
    {
        if (numPlayers > 2)
        {
            printf(RED "The player %s has been deleted as it has no more moves available.\n The game continues with the remaining players!\n" RESET, player[i].name);
            delete_player(i);
            return 1;
        }
        else
        {
            printf(RED "The player %s has been deleted as it has no more moves available.\n" RESET, player[i].name);
            delete_player(i);
            if (i == 1)
                win(0);
            else
                win(1); // it implies that player[0] won
            return 1;
        }
    }
    return 0;
}

int main()
{

    // printf("\033[45m");
    // printf(BACKGROUND);
    // printf("\xF0\x9F\x91\xA7\n");
    initialize_game();
    print_legend();
    int ok = 1;
    while (ok)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (cant_climb_anymore(i) == 1)
            {
                if (numPlayers > 2)
                {
                    printf(RED "The player %s has been deleted as it has no more moves available.\n The game continues with the remaining players!\n" RESET, player[i].name);
                    delete_player(i);
                    return 1;
                }
                else
                {
                    printf(RED "The player %s has been deleted as it has no more moves available.\n" RESET, player[i].name);
                    delete_player(i);
                    if (i == 1)
                        win(0);
                    else
                        win(1); // it implies that player[0] won
                    return 1;
                }
            }
            moving(i);
            if (cant_build_anymore(i) == 1)
            {
                if (numPlayers > 2)
                {
                    printf(RED "The player %s has been deleted as it has no more moves available.\n The game continues with the remaining players!\n" RESET, player[i].name);
                    delete_player(i);
                    return 1;
                }
                else
                {
                    printf(RED "The player %s has been deleted as it has no more moves available.\n" RESET, player[i].name);
                    delete_player(i);
                    if (i == 1)
                        win(0);
                    else
                        win(1); // it implies that player[0] won
                    return 1;
                }
            }
            building(i);
        }
    }

    return 0;
}
