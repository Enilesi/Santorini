#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define MAX_LINE_LENGHT 1000
//col 1 3 7
//sortata dupa an->titlu cu strcmp
//dau eu niste valori de an diferite
//parcurg de la head la tail si la fiecare nod fac free
//la ex putem primi sa se sparga o lista in doua=> head 1 head 2 si tail 1 tail 2
typedef struct _movies
{
    unsigned int year;
    char title[MAX];
    char budget[MAX];
    struct _movies *next;
}movie;
movie *head,*tail,*crt;

void init_list(movie ** head, movie ** tail)
{
    *head=*tail=NULL;
}

movie *create_movie(int year, char title[], char budget[])
{
    movie *p;
    p=(movie *)malloc(sizeof(movie));
    if(NULL==p)
    {
        printf("Error at memory allocation.\n");
        exit(1);
    }
    p->year=year;
    strcpy(p->title,title);
    strcpy(p->budget,budget);
    p->next=NULL;
    return p;
}

void print_list(movie *head)
{
    movie *p;
    if(NULL==head)
        printf("Empty list\n");
    else
    {
        p=head;
        while(p)
        {
            printf("Year: %d; Title: %s; Budget: %s\n",p->year,p->title,p->budget);
            p=p->next;
        }
        printf("\n");
    }
}

void add_to_front(movie *movie_to_add, movie ** head, movie ** tail)
{
    movie_to_add->next=*head;
    if(NULL==*head)
    {
        *tail=movie_to_add;
    }
    *head=movie_to_add;
}

void add_to_back(movie *movie_to_add, movie **head, movie **tail)
{
    if(NULL==*tail)
        *head=movie_to_add;
    else
        (*tail)->next=movie_to_add;
    *tail=movie_to_add;
    movie_to_add->next=NULL;
}

void add_ordered(movie *movie_to_add, movie **head, movie **tail)
{
    if (!*head || movie_to_add->year < (*head)->year ||
        (movie_to_add->year == (*head)->year && strcmp(movie_to_add->title, (*head)->title) <= 0))
    {
        add_to_front(movie_to_add, head, tail);
    }
    else
    {
        movie *before = NULL, *after = *head;
        while (after && (after->year < movie_to_add->year ||
                         (after->year == movie_to_add->year && strcmp(after->title, movie_to_add->title) < 0)))
        {
            before = after;
            after = after->next;
        }
        if (!after || movie_to_add->year < after->year ||
            (movie_to_add->year == after->year && strcmp(movie_to_add->title, after->title) <= 0))
        {
            before->next = movie_to_add;
            movie_to_add->next = after;
        }
        else
        {
            add_to_back(movie_to_add, head, tail);
        }
    }
}


movie* safe_realloc(movie* ptr, size_t item_size, int count) {
  size_t new_size = item_size * (count + 1);
  movie* new_ptr = realloc(ptr, new_size);

  if (new_ptr == NULL) {
    perror("realloc failed");
    free(ptr); 
    return NULL;
  }

  return new_ptr;
}
void free_list(movie *head)
{
    movie *curr=head;
    movie *next;
    while(curr!=NULL)
    {
        next=curr->next;
        free(curr);
        curr=next;
    }
}

int no_more_moves(int i)
{
    
}
int main(int argc, char *argv[])
{
    if (argc != 2) {
         printf("Invalid command line arguments.\n");
         return 1;
     }

    FILE * file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
     char line[MAX_LINE_LENGHT];
    init_list(&head, &tail);
    //movie *movies = safe_realloc(NULL,sizeof(movie),1);
    int movies_count=0;

    fgets(line, sizeof(line), file);
    while(fgets(line,sizeof(line),file))
    {
        unsigned int year;
        char imdb[MAX];
        char title[MAX];
        char test[MAX],clean_test[MAX],binary[MAX];
        char budget[MAX];
        int nr=0;
        if(sscanf(line,"%u,%[^,],%n",&year,imdb,&nr)==2)
        {
            if(line[nr]=='\"')
            {
                if(sscanf(line+nr,"\"%[^\"]\",%[^,],%[^,],%[^,],%[^,]",title,test,clean_test,binary,budget)==5)
                {
                    //movies=safe_realloc(movies,sizeof(movie),movies_count+1);
                    movie *movie1=create_movie(year,title,budget);
                    add_ordered(movie1,&head,&tail);

                }
            }
            else 
            {
               if(sscanf(line+nr,"%[^,],%[^,],%[^,],%[^,],%[^,]",title,test,clean_test,binary,budget)==5)
                {
                    //movies=safe_realloc(movies,sizeof(movie),movies_count+1);
                    movie *movie1=create_movie(year,title,budget);
                    add_ordered(movie1,&head,&tail);

                } 
            }

        }
    }
    print_list(head);
    free_list(head);
    return 0;
}