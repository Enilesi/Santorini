#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BOARD_SIZE 5

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
    char name[50];
}Player;

Player player[4];
int board[BOARD_SIZE][BOARD_SIZE];
int numPlayers;

void err( char *message)
{
    printf("%s",message);
    exit(1);
}

void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void init_4_players(int i)
{
    printf("Enter gender of %s's worker:\n G-girl\n B-boy\n",player[i].name);
    clear_input_buffer();
    if (scanf("%c", &player[i].worker[1].gender) != 1) 
        {
            err("Error reading worker's gender");
        }
    
    if((i==2||i==4)&&player[i].worker[1].gender==player[i-1].worker[1].gender)
    {
            err("Invalid choice. Two teammates can't have the same gender for a worker");
    }

    printf("Enter the color of %s's worker:\n B-blue\n G-gray\n W-white\n",player[i].name);
    clear_input_buffer();
    if (scanf("%c", &player[i].worker[1].color) != 1) 
        {
            err("Error reading worker's color");
        }

    if((i==2||i==4)&&player[i].worker[1].color!=player[i-1].worker[1].color)
    {
            err("Invalid choice. Two teammates must have the same color for their workers");
    }

}

void init_not_4_players(int i)
{
    player[i].worker[1].gender='G';
    player[i].worker[2].gender='B';

    printf("Enter the color of %s's workers:\n B-blue\n G-gray\n W-white\n",player[i].name);
    clear_input_buffer();
    if (scanf("%c", &player[i].worker[1].color) != 1) 
        {
            err("Error reading worker's color");
        }

    if(i%2==0&&player[i].worker[1].color!=player[i-1].worker[1].color)
        {
            err("Error reading worker's color: two teammates must have the same colors!");
        }
    player[i].worker[2].color=player[i].worker[1].color;
}

void initialize_game() 
{
    printf("Enter the number of players: ");
    if (scanf("%d", &numPlayers) != 1) 
    {
        err("Error reading number of players");
    }
    if (numPlayers < 2 || numPlayers > 4) 
    {
        err("Invalid. Number of players must be between 2 and 4. Exiting.\n");
    }
    for (int i = 1; i <= numPlayers; i++) 
    {
        if(numPlayers==4)
        {
            if(i==1)printf("Enter first team:\n");
            else if(i==3)printf("Enter second team:\n");
        }
        printf("Enter the name for player:\n");
        if (scanf("%49s", player[i].name) != 1) 
        {
            err("Error reading player name");
        }
        
        if(numPlayers==4)
            init_4_players(i);
        else 
            init_not_4_players(i);
        player[i].worker[1].position.x = -1;
        player[i].worker[1].position.y = -1;
        player[i].worker[2].position.x = -1;
        player[i].worker[2].position.y = -1;
        
    }
}

void print_board()
{
    for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            printf("%2d",board[i][j]);
            printf("\n");
        }
} 


int is_valid_move(int x, int y, Worker worker)
{
    if(board[x][y]==4) return 0;
    if((x||y)<0||((x||y)>5)) return 0;
    for(int i=1;i<=numPlayers;i++)
        {
            if(player[i].worker[1].position.x==x||player[i].worker[1].position.y==y||player[i].worker[2].position.x==x||player[i].worker[2].position.y==y)
            return 0;
        }
    if(board[x][y]>board[worker.position.x][worker.position.y])
        {
            if(board[x][y]-board[worker.position.x][worker.position.y]>1)
                return 0;
            else 
                return 1;
         }
    else 
        return 1;
    return 1;
}

void construct_building(int x, int y)
{

    //must check if worker on that position or board is 3
    for(int i=1;i<=4;i++)
        for(int j=1;j<=2;j++)
        {
            if(player[i].worker[j].position.x==x&&player[i].worker[j].position.y==y)
                printf("Change coordinates; You can't burry a worker in a building");
        }

}


//i must create a struct for the dome because not every time i put a dome is a win
//or pay attention that not always 4= win on the board
//CSV for tomorrow
//merge+insertion => timsort and why is eff more than them

int main()
{
    // int opt=1;
    print_board();
    //printf("MENU/n 1.initialize game");
    initialize_game();
    return 0;
}


