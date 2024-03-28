#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
#include<ctype.h> //for strch
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
    player[i].worker[2].color=player[i].worker[1].color;
}

void initialize_game() 
{

    printf("LET'S START THE GAME!\n\nEnter the number of players: ");
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
            if(i==1)printf("\n\nEnter first team:\n");
            else if(i==3)printf("\n\nEnter second team:\n");
        }
        switch (i)
        {
        case 1:
            printf("\nEnter the name for first player:\n");
            break;
        case 2:
            printf("\nEnter the name for second player:\n");
            break;
        case 3:
            printf("\nEnter the name for third player:\n");
            break;
        case 4:
            printf("\nEnter the name for fourth player:\n");
            break;
        
        default:
            break;
        }
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

void win(int i, int j)
{
    if(numPlayers!=4)
        {
            printf(" THE GAME IS OVER!\n%s won the chalenge",player[i].name);
            exit(0);
        }
    else
        {
            if(i<3)
                {
                    printf(" THE GAME IS OVER!\nThe first team composed of %s and %s won the chalenge",player[1].name, player[2].name);
                    exit(0);
                }
            else 
                {
                    printf(" THE GAME IS OVER!\nThe second team composed of %s and %s won the chalenge",player[3].name, player[4].name);
                    exit(0);
                }
            
        }
}

void construct_building(int x, int y, int i, int j)
{

    for(int i=1;i<=4;i++)
        for(int j=1;j<=2;j++)
        {
            if(player[i].worker[j].position.x==x&&player[i].worker[j].position.y==y)
                {
                    printf("Invalid move. Get new position for the building:");
                    return;
                }
            
        }
    if(board[x][y]==3)
        {
            win(i,j);
        }
    board[x][y]++;

}


int move_worker(int x, int y,int i,int j)
{
    if(board[x][y]==3)
        {
                win(i,j);
        }
    if(is_valid_move(x,y,player[i].worker[j]))
       {
            player[i].worker[j].position.x=x;
            player[i].worker[j].position.y=y;
            return 1;
       }
  return 0;

}

//i must implement in main to have a 

// i must check the colors to corespond
//sa fac matricea char si sa pun D in loc de 4

int main()
{

    initialize_game();
    int x,y;
    printf("\nIntroduce the coordinates of the workers (0->5)\nThe format is:\nx y\n");
    scanf("%d %d",&x,&y);
    int m=move_worker(x,y,1,1);
    if(m==0)
        {
            printf("Ivalid move. Get new position for the worker:");
        }
    
    print_board();
    return 0;
}