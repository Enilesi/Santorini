#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h> //for strch
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


#define RESET   "\033[m"

#define ROWS 4
#define COLUMNS 8
#define LEN_CASES 15

//i must do a function to check if no more moves and if so=> 
typedef struct 
{
    int x;
    int y;
}Position;

typedef struct
{
    Position position;
    char color;
    char gender;
}Worker;

typedef struct
{
    Worker worker[2];
    char name[50]; //i shall do a function to verify if players have the same name, and if so, i must add an index
}Player;

typedef struct 
{
    Position position;
}Dome;


Player player[4];
int board[BOARD_SIZE][BOARD_SIZE];
int numPlayers;
int level1, level2, level3, domes;
Dome dome[MAX_DOMES];

void err( char *message)
{
    printf("%s",message);
    exit(1);
}

void initialize_domes() {
    int i;
    for (i = 0; i < MAX_DOMES; i++) {
        dome[i].position.x = -1;
        dome[i].position.y = -1;
    }
}


void init_4_players(int i)
{
    printf("Enter gender of %s's worker:\n G-girl\n B-boy\n", player[i].name);

    if (scanf(" %c", &player[i].worker[0].gender) != 1) 
    {
        err("Error reading worker's gender");
    }
    
    if ((i == 1 || i == 3) && player[i].worker[0].gender == player[i - 1].worker[0].gender)
    {
        err("Invalid choice. Two teammates can't have the same gender for a worker");
    }

     printf("Enter the color of %s's worker:\n ->P-pink "PINK_HIGHLIGHT" "HIGHLIGHT_RESET"\n ->G-green "GREEN_HIGHLIGHT" "HIGHLIGHT_RESET"\n ->B-blue " BLUE_HIGHLIGHT" "HIGHLIGHT_RESET"\n \n", player[i].name);
 
    if (scanf(" %c", &player[i].worker[0].color) != 1) 
    {
        err("Error reading worker's color");
    }

    if (player[i].worker[0].color != 'P' && player[i].worker[0].color != 'G' && player[i].worker[0].color != 'B')
    {
        err("Invalid choice. Worker's color must be 'B', 'P', or 'G'");
    }

    if ((i == 1 || i == 3) && player[i].worker[0].color != player[i - 1].worker[0].color)
    {
        err("Invalid choice. Two teammates must have the same color for their workers");
    }
}


void init_not_4_players(int i)
{
    player[i].worker[0].gender='G';
    player[i].worker[1].gender='B';

    int ok=1;
    while(ok==1)
    {
        int cond=1;
        printf("\nEnter the color of %s's worker:\n ⟶ P: pink "PINK_HIGHLIGHT" "HIGHLIGHT_RESET"\n ⟶ G: green "GREEN_HIGHLIGHT" "HIGHLIGHT_RESET"\n ⟶ B: blue " BLUE_HIGHLIGHT" "HIGHLIGHT_RESET"\n \n", player[i].name);
        scanf(" %c", &player[i].worker[0].color); 
        if(player[i].worker[0].color!='P'&&player[i].worker[0].color!='B'&&player[i].worker[0].color!='G')
            {
                printf("Invalid color given. Try again!\n");
                cond=0;
            }
        else if(i>0)
        {
            for(int j=i-1;j>=0;j--)
                if(player[i].worker[0].color==player[j].worker[0].color)
                {
                    printf("Invalid color given. Two different players can't share a color!\n");
                    cond=0;
                }
        }
        if (cond==1)ok=0;
    }
    player[i].worker[1].color=player[i].worker[0].color;
}

void print_header()
{
    char text[] = "LET'S START THE GAME!\n";
    char *word = strtok(text, " \n");
    int colorIndex = 0;

    while (word != NULL) {
        switch (colorIndex % 3) {
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
    //printf("\033[45m");
    print_header();
    printf("\n\nEnter the number of players: ");
    if (scanf("%d", &numPlayers) != 1) 
    {
        err("Error reading number of players");
    }
    if (numPlayers < 2 || numPlayers > 4) 
    {
        err("Invalid. Number of players must be between 2 and 4. Exiting.\n");
    }
    for (int i = 0; i < numPlayers; i++) 
    {
        if(numPlayers==4)
        {
            if(i==0)printf("\n\nEnter first team:\n");
            else if(i==2)printf("\n\nEnter second team:\n");
        }
        switch (i)
        {
        case 0:
            printf("\nEnter the name for first player:\n");
            break;
        case 1:
            printf("\nEnter the name for second player:\n");
            break;
        case 2:
            printf("\nEnter the name for third player:\n");
            break;
        case 3:
            printf("\nEnter the name for fourth player:\n");
            break;
        
        default:
            break;
        }
        scanf("%s", player[i].name); 
        
        if(numPlayers==4)
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
    for(int k = 0; k < numPlayers; k++)
        for(int l = 0; l < 2; l++)
            if(player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                return 1;
    return 0;
}

void print_worker(int x, int y)
{
    for(int k = 0; k < numPlayers; k++)
        for(int l = 0; l < 2; l++)
            {
                if(player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                    {
                        switch (player[k].worker[l].color)
                        {
                        case 'G':printf("\033[0;37;40m %c%d \033[0m", player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                            break;
                        case 'W':printf("\033[0;30;47m %c%d \033[0m",player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                            break;
                        case 'B':printf("\033[0;37;44m %c%d \033[0m",  player[k].worker[l].gender, l + 1); /// l for B1 B2 G1 G2
                            break;
                        default:printf("N");
                            break;
                        }
                    }
            }
}
void print_legend() {
    printf("Map:\n");
    for(int i = 0; i < numPlayers; i++) {
        if(player[i].name) {
            printf("%10s:", player[i].name);
            for(int j = 0; j < 2; j++) {
                if(player[i].worker[j].color) {
                    switch (player[i].worker[j].color) {
                        case 'P':
                            printf(PINK_HIGHLIGHT " %c%d " HIGHLIGHT_RESET, player[i].worker[j].gender, j+1); /// l for B1 B2 G1 G2
                            break;
                        case 'B':
                            printf(BLUE_HIGHLIGHT" %c%d "HIGHLIGHT_RESET, player[i].worker[j].gender, j+1); /// l for B1 B2 G1 G2
                            break;
                        case 'G':
                            printf(GREEN_HIGHLIGHT" %c%d "HIGHLIGHT_RESET, player[i].worker[j].gender, j+1); /// l for B1 B2 G1 G2
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
    {
        {"             "},
        {"             "},
        {"             "},
        {"             "},
        {"   __________"},
        {"  /         /"},
        {" /         / "},
        {"/_________/  "}
    },
    {
        {"             "},
        {"             "},
        {"             "},
        {"   _________ "},
        {"  /        /|"},
        {" /________/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"             "},
        {"             "},
        {"   ________  "},
        {"  /______ /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"             "},
        {"    ______   "},
        {"   /_____/|  "},
        {"  |__3__| /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    }
};

char cases_dome[ROWS][COLUMNS][LEN_CASES] = {
    {
        {"             "},
        {"             "},
        {"             "},
        {"             "},
        {"   ___D_____ "},
        {"  / /__/|   /"},
        {" / |__|/   / "},
        {"/_________/  "}
    },
    {
        {"             "},
        {"             "},
        {"             "},
        {"   ___D_____ "},
        {"  / /__/|  /|"},
        {" /_|__|/__/ |"},
        {"|   1    | / "},
        {"|________|/  "}
    },
    {
        {"             "},
        {"     _D_     "},
        {"    /__/|__  "},
        {"  /_|__|/_/| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"      _D_    "},
        {"    _/__/|_  "},
        {"   /|__|//|  "},
        {"  |__3__| /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    }
};

char cases_girl[ROWS][COLUMNS][LEN_CASES] = {
    {
        {"             "},
        {"             "},
        {"             "},
        {"             "},
        {"   __*0*_____"},
        {"  /  /|\\    /"},
        {" /   / \\   / "},
        {"/_________/  "}
    },
    {
        {"             "},
        {"             "},
        {"     *0*     "},
        {"   __/|\\____ "},
        {"  /  / \\   /|"},
        {" /________/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"             "},
        {"     *0*     "},
        {"   __/|\\___  "},
        {"  /__/_\\_ /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"     *0*     "},
        {"    _/|\\__   "},
        {"   /_/_\\_/|  "},
        {"  |__3__| /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    }
};

char cases_boy[ROWS][COLUMNS][LEN_CASES] = {
    {
        {"             "},
        {"             "},
        {"             "},
        {"             "},
        {"   ___0______"},
        {"  /  /|\\    /"},
        {" /   / \\   / "},
        {"/_________/  "}
    },
    {
        {"             "},
        {"             "},
        {"      0      "},
        {"   __/|\\____ "},
        {"  /  / \\   /|"},
        {" /________/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"             "},
        {"      0      "},
        {"   __/|\\___  "},
        {"  /__/_\\_ /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    },
    {
        {"      0      "},
        {"    _/|\\__   "},
        {"   /_/_\\_/|  "},
        {"  |__3__| /| "},
        {" |   2   | /|"},
        {" |_______|/ |"},
        {"|    1    | /"},
        {"|_________|/ "}
    }
};

int search_player_worker_pos(int x, int y)
{
    for(int k = 0; k < numPlayers; k++)
        for(int l = 0; l < 2; l++)
                if(player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                    return k;
    return -1;
}
int search_worker_pos(int x, int y)
{
    for(int k = 0; k < numPlayers; k++)
        for(int l = 0; l < 2; l++)
                if(player[k].worker[l].position.x == x && player[k].worker[l].position.y == y)
                    return l;
    return -1;
}

void indented_space(int i) {
    int j;
    for (j = 0; j < i; j++) {
        printf(" ");
    }
}

int check_if_exists_dome_on_that_pos(int x, int y)
{
    for(int i=0;i<domes;i++) //changed from max domes
        if( dome[i].position.x==x&&dome[i].position.y==y&&dome[i].position.x!=-1)
            return 1;
    return 0;
}
void print_board() 
{
    for (int i = 0; i < BOARD_SIZE; i++)
     {
        for (int k = 0; k < COLUMNS; k++)
         { indented_space(7*(BOARD_SIZE-i));//or 10
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
                else if(check_if_exists_dome_on_that_pos(i,j))
                {
                    printf("%s      ", cases_dome[board[i][j]][k]);
                }
                else 
                {
                    printf("%s      ", cases_simple[board[i][j]][k]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    print_legend();
}

int is_valid_move(int x, int y, int index_i, int index_j) {

    if(check_if_exists_dome_on_that_pos(x,y)==1)return 0;

    if(board[x][y] == 4) return 0; //if dome

    if((x < 0 || y < 0) || ((x >= BOARD_SIZE || y >= BOARD_SIZE))) return 0;
    for(int i = 0; i < numPlayers; i++) {
        if((player[i].worker[0].position.x == x && player[i].worker[0].position.y == y )|| (player[i].worker[1].position.x == x && player[i].worker[1].position.y == y)&&index_i!=i)
            return 0;
    }
    if(board[x][y] > board[player[index_i].worker[index_j].position.x][player[index_i].worker[index_j].position.y]) {
        if(board[x][y] - board[player[index_i].worker[index_j].position.x][player[index_i].worker[index_j].position.y] > 1)
            return 0;
        else 
            return 1;
    }
    else 
        return 1;
    return 1;
}


void win(int i) {
    if(numPlayers != 4) {
        print_board();
        printf(" THE GAME IS OVER!\n%s won the chalenge\n", player[i].name);
        exit(0);
    }
    else {
        if(i < 2) {
            print_board();
            printf(" THE GAME IS OVER!\nThe first team composed of %s and %s won the chalenge\n", player[0].name, player[1].name);
            exit(0);
        }
        else {
            print_board();
            printf(" THE GAME IS OVER!\nThe second team composed of %s and %s won the chalenge\n", player[2].name, player[3].name);
            exit(0);
        }
    }
}

int building_in_the_corners(int x, int y, int i, int l)
{

            
    if(x==0&&y==0)
        {
            if((player[i].worker[l].position.x==0&&player[i].worker[l].position.y==1)||
                (player[i].worker[l].position.x==1&&player[i].worker[l].position.y==1)||
                    (player[i].worker[l].position.x==1&&player[i].worker[l].position.y==0))
                        return 1;
        }
    else if(x==4&&y==0)
        {
            if((player[i].worker[l].position.x==3&&player[i].worker[l].position.y==0)||
                (player[i].worker[l].position.x==3&&player[i].worker[l].position.y==1)||
                    (player[i].worker[l].position.x==4&&player[i].worker[l].position.y==1))
                        return 1;
        }
    else if(x==0&&y==4)
    {
            if((player[i].worker[l].position.x==0&&player[i].worker[l].position.y==3)||
                (player[i].worker[l].position.x==1&&player[i].worker[l].position.y==3)||
                    (player[i].worker[l].position.x==1&&player[i].worker[l].position.y==4))
                        return 1;
    }
    else if(x==0&&y==4)
        {
            if((player[i].worker[l].position.x==3&&player[i].worker[l].position.y==4)||
                (player[i].worker[l].position.x==3&&player[i].worker[l].position.y==3)||
                    (player[i].worker[l].position.x==4&&player[i].worker[l].position.y==3))
                        return 1;
        }
    return 0;
}

int is_building_in_the_boder(int x, int y, int i, int l)
{
    if(building_in_the_corners(x,y,i,l)==1) return 1;
    else
        {
            if(y==0)
                {
                    if((player[i].worker[l].position.x==x-1&&player[i].worker[l].position.y==y)||
                        (player[i].worker[l].position.x==x&&player[i].worker[l].position.y==y+1)||
                            (player[i].worker[l].position.x==x+1&&player[i].worker[l].position.y==y)||
                                (player[i].worker[l].position.x==x-1&&player[i].worker[l].position.y==y+1)||
                                    (player[i].worker[l].position.x==x+1&&player[i].worker[l].position.y==y+1)
                                )
                                return 1;
                }
            else if(y==4)
                {
                    if((player[i].worker[l].position.x==x-1&&player[i].worker[l].position.y==y)||
                        (player[i].worker[l].position.x==x&&player[i].worker[l].position.y==y-1)||
                            (player[i].worker[l].position.x==x+1&&player[i].worker[l].position.y==y)||
                                (player[i].worker[l].position.x==x-1&&player[i].worker[l].position.y==y-1)||
                                    (player[i].worker[l].position.x==x+1&&player[i].worker[l].position.y==y-1)
                                )
                                return 1;
                }
        }
    return 0;
}

int is_building_not_in_the_border(int x, int y, int i, int l) {
    if(check_if_exists_dome_on_that_pos(x,y)==1)return 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((x + dx >= 0 && x + dx < BOARD_SIZE) && 
                (y + dy >= 0 && y + dy < BOARD_SIZE) &&
                (dx != 0 || dy != 0) && 
                player[i].worker[l].position.x == x + dx &&
                player[i].worker[l].position.y == y + dy) {
                    return 1;
            }
        }
    }
    return 0;
}


int is_valid_position_building(int x, int y, int i)
{
    if(check_if_exists_dome_on_that_pos(x,y)==1)return 0;

    for(int k = 0; k < 4; k++)
        for(int l = 0; l < 2; l++) {
            if(player[k].worker[l].position.x == x && player[k].worker[l].position.y == y) {  //no building over worker
                return 0;
            }
        }
    if(player[i].worker[0].position.x==-1&&player[i].worker[1].position.x==-1) //if it's your first time ever building
        return 1;
    int len;// how many workers each player has
    if(numPlayers==4) len=1;
    else len=2;

    for(int l = 0; l < len; l++)//must verify if worker exists because i can have 4 players
        {
            if(is_building_in_the_boder(x,y,i,l)==1||is_building_not_in_the_border(x,y,i,l)==1)
                return 1;
        }
    
    return 0;
}

int construct_building(int x, int y, int i) {
    if(is_valid_position_building(x,y,i)==1)
    {
        switch (board[x][y])
        {
        case 0: if(level1<=22){board[x][y]++;level1++;return 1;}
        case 1: if(level2<=18){board[x][y]++;level2++;return 1;}
        case 2: if(level3<=14){board[x][y]++;level3++;return 1;}
        case 3: win(i);return 1;
        
        default:return 0;
        }
    }
    return 0;
}

int move_worker(int x, int y, int i, int j) {
    if(board[x][y] == 3)
        win(i);
    if(is_valid_move(x, y, i,j)) { //i must also implement an else 
        player[i].worker[j].position.x = x;
        player[i].worker[j].position.y = y;
        return 1;
    }
    return 0;
}

int search_worker_index(int gender, int i)
{
    int len;
    if(numPlayers==4)len=1;
    else len=2;
 
    for(int l = 0; l < len; l++)
        if(player[i].worker[l].gender==gender)
            return l;
   return -1;
}
int check_if_exists_worker_ont_that_pos(int x,int y)
{
    int len=2;
    if(numPlayers==4)len=1;
    for(int i=0;i<numPlayers;i++)
        {
            for(int j=0;j<len;j++)
                if(player[i].worker[j].position.x==x&&player[i].worker[j].position.y==y)
                    return 1;
        }
    return 0;
}
int construct_dome(int pos_x,int pos_y) //i shall check if worker on that position
{
    if(domes==18)
    {
        printf("Can't build domes anymore");
        return -1;
    }
    if(check_if_exists_worker_ont_that_pos(pos_x,pos_y)==1) return 0;
    if(check_if_exists_dome_on_that_pos(pos_x,pos_y)==0)
    {
            dome[domes].position.x=pos_x; ///or to 1, I shall think in the future
            dome[domes].position.y=pos_y;
            domes++;
            return 1;
    }
    return 0;
}

void print_atlas()
{
    printf(GOLD);

    printf("                                                            \n");
    printf("                                                            \n");
    printf("                           .::::.                          \n");
    printf("                       .-===-::.:-===-                      \n");
    printf("                     -=:  .   :   .  .==.                   \n");
    printf("                   .+:   .    :    :   .-=                  \n");
    printf("                  .+:...-.....=.....-...-:+                 \n");
    printf("                  +..   :     -     :    .:=                \n");
    printf("                 -*#+  ..     -     :    . *                \n");
    printf("                 +@@=::-::::::=:::::=::::-:*                \n");
    printf("                 :%%%% ..     -     :    .   *                \n"); 
    printf("                 -@@@   :     -     :    .-:                \n");
    printf("                 %%@@@:..-:....=--:.:-...:=-                 \n");
    printf("                :@@@@=   :  =@%%%%#=:   :=+=                 \n");
    printf("                +@@@%%*-. . =#@%%#: .-=*#@#                 \n");
    printf("                .#@@##%%@#*===+%%@#+-=+=+#@@%%                 \n");
    printf("                  .+%%@@@@@%%#%%%%%%#+=@@%%@@@+                 \n");
    printf("                     :*%%@@@@@@@@#@@*@@@%%+.                  \n");
    printf("                      .@@%%@@@@@@*@@@-.                      \n");
    printf("                       .%%@#%%%%#*@@@=                        \n");
    printf("                        =@@%%%%@@#-                          \n");
    printf("                        =@@%%@%%%%                           \n");
    printf("                       -*%%%%####*.                         \n");
    printf("                       #*##%%@@##+*##-                      \n");
    printf("                      .@%%@@@@@%%*%%@@%%*:                    \n");
    printf("                      *@@@@@@@@%%*@@@@@#@=                   \n");
    printf("                .    :#@@@@@@@#-##*%%@@@%%.                   \n");
    printf("               =@@@@@@+@%%%%://     :@@@%%.                    \n");
    printf(RESET);
}



int god_power(int i)
{
    int ok=1;
    while(ok==1)
    {
        printf("\nDo you want to use the God Power?\n");
        print_atlas();
        printf("Yes/No\n");
        char answear[4];
        scanf("%s",answear);
        if(strcmp(answear,"Yes")==0)
        {
            ok=0;
            return 1;
        }
        else if(strcmp(answear,"No")==0)
        {
            ok=0;
            return 0;
        }
        else 
        {
            printf("Invalid answear. Try again!");
        }
    }
   
}

int doming(int i)
{
    if(god_power(i)==1)
    {

        int ok=1;
        while(ok==1)
            {
                printf("Give your coordinates for the dome(0->4) with the format:\nx y\n");
                int dome_x,dome_y;
                scanf("%d %d",&dome_x,&dome_y); //I shall implement sth for invalid integers also
                int answear=construct_dome(dome_x,dome_y);
                if(answear==1)
                    {
                        printf("\nThe game looks now like this:\n");
                        print_board();
                        printf("\n");
                        ok=0;
                        return 1;
                    }
                else if(answear==0)
                {
                    printf("Invalid coordinates for the dome. Try again!");
                }
                else if(answear==-1)
                {
                    return 0;
                }
            }
        }
    return 0;
}

void building(int i)
{
    printf("\nLET'S BUILD!\nThe game looks like this:\n");
    print_board();
    if(doming(i)==0)
    {
        int ok=1;
        while(ok==1)
        {
            printf("Give your coordinates for the building(0->4) with the format:\nx y\n");
            int building_x,building_y;
            scanf("%d %d",&building_x,&building_y);
            if(construct_building(building_x,building_y,i)==1)
                {
                    printf("\nThe game looks now like this:\n");
                    print_board();
                    printf("\n");
                    ok=0;
                }
            else
            {
                printf("Invalid choice for the building. Try again!");
            }
        }
    }
}

void moving(int i)
{
    printf("\nLET'S MOVE!\nThe game looks like this:\n");
    print_board();
    int ok1=1;
    int worker_index;
    char gender;
    while(ok1==1)
    {
        printf("Give the gender of your worker, %s:\nB/G \n",player[i].name);
        scanf(" %c",&gender);
        worker_index=search_worker_index(gender,i);
        if(worker_index==-1)
            {
                printf("Invalid choice. Choose an existing worker!\n");
            }
        else
        {
            ok1=0;
        }
    }

    int ok2=1;
    while(ok2==1)
    {
        printf("Give the coordinates for your worker (0->4),%s, with the format:\nx y\n",player[i].name);
        int worker_x,worker_y;
        scanf("%d %d",&worker_x,&worker_y);
        if(move_worker(worker_x,worker_y,i,worker_index)==1)
            {
            printf("\nThe game looks now like this:\n");
            print_board();
            printf("\n");
            ok2=0;
        }
        else
        {
            printf("Invalid choice. Choose a other coordinates for the worker!\n");
        }
    }
}

int main() 
{

    //printf("\033[45m");
    //printf(BACKGROUND);
    initialize_game();
    print_legend();
    int ok=1;
    while(ok)
    {
        for(int i=0;i<numPlayers;i++)
        {
            printf("%s, give your first option: build or move\n",player[i].name); // i must do a function to det if no valid moves=>win  //2 players=> the other wins; 3 players=> the oth 2 continue the game
            char option[2][6];
            scanf("%6s",option[0]);
            if (strcmp(option[0],"build")==0)
            {
                building(i);
                moving(i);
            }
            else if (strcmp(option[0],"move")==0)
            {
                moving(i);
                building(i);
            }
            else
            {
                printf("Inexistent option, try again!");
                i--;
            }
                
        }
                
            
             
    }


    return 0;
}
