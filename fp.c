#include<stdio.h>
#include <stdlib.h>
struct shapes2D
{
    int flag_type;
    union data 
        {
            struct circle { int radius; int x,y;}c;
            struct square { int x1, x2, y1, y2;}s;
            struct triangle { int x1, x2, x3, y1, y2, y3;}t;
        }u;
    void (*insert_shape)(struct shapes2D *shapelist);
    void(*print_surface)(struct shapes2D *shapelist);
    void (*print_shape)(struct shapes2D *shapelist);

}shapelist[100];

int shape_count=0;

void insert_shape()
{
    printf(" Insert: \n 1-for cirle;\n 2-for square;\n 3-for triangle\n");
    scanf("%d",&shapelist[shape_count].flag_type);
    switch(shapelist[shape_count].flag_type)
    {
        case 1: scanf("%d %d %d",&shapelist[shape_count].u.c.radius,&shapelist[shape_count].u.c.x,&shapelist[shape_count].u.c.y);
                break;
        case 2: scanf("%d %d %d %d",&shapelist[shape_count].u.s.x1,&shapelist[shape_count].u.s.x2,&shapelist[shape_count].u.s.y1,&shapelist[shape_count].u.s.y2);
                break;
        case 3: scanf("%d %d %d %d %d %d",&shapelist[shape_count].u.t.x1,&shapelist[shape_count].u.t.x2,&shapelist[shape_count].u.t.x3,&shapelist[shape_count].u.t.y1,&shapelist[shape_count].u.t.y2,&shapelist[shape_count].u.t.y3);
                break;
        default:
            printf("Invalid input.\n");
            break;
    }
    shape_count++;
    
}

void show_shapes()
{
    if (shape_count == 0)
    {
        printf("There are no shapes.\n");
       
    } 
    else
    {
        printf("There exist shapes.\n");
        for( int i=0; i<shape_count;i++)
        {
            switch(shapelist[i].flag_type)
            {
                case 1: printf("Type: circle, radius:%d, x:%d, y:%d\n",shapelist[i].u.c.radius,shapelist[i].u.c.x,shapelist[i].u.c.y);
                        break;
                case 2: printf("Type: square, x1:%d, x2:%d, y1:%d, y2:%d\n",shapelist[i].u.s.x1,shapelist[i].u.s.x2,shapelist[i].u.s.y1,shapelist[i].u.s.y2);
                        break;
                case 3: printf("Type: triangle, x1:%d, x2:%d, x3:%d, y1:%d, y2:%d, y3:%d\n",shapelist[i].u.t.x1,shapelist[i].u.t.x2,shapelist[i].u.t.x3,shapelist[i].u.t.y1,shapelist[i].u.t.y2,shapelist[i].u.t.y3);
                        break;

            }
        }
    }
}

void print_surface()
{
    printf("\nSURFACES:\n");
    for(int i=0;i<shape_count;i++)
    {
        switch(shapelist[i].flag_type)
            {
                case 1: printf("Type: circle, surface: %lf\n",2*3.14*shapelist[i].u.c.radius);

                case 2: printf("Type: square, surface: %d\n",abs(shapelist[i].u.s.x1-shapelist[i].u.s.x2)*abs(shapelist[i].u.s.y1-shapelist[i].u.s.y2));
                        break;
                case 3: int a=shapelist[i].u.t.x1*shapelist[i].u.t.y2+shapelist[i].u.t.x2*shapelist[i].u.t.y3+shapelist[i].u.t.x3*shapelist[i].u.t.y1;
                        int b=shapelist[i].u.t.x1*shapelist[i].u.t.y3+shapelist[i].u.t.x2*shapelist[i].u.t.y1+shapelist[i].u.t.x3*shapelist[i].u.t.y2;
                        printf("Type: triangle, surface: %d\n",abs(a-b)/2);
                        break;

            }
    }
}

int main()
{
    int opt=-1;
    while (opt!=0)
    {
        printf("\nMENU:\n 0.Exit programme \n 1.Insert new shapes\n 2.Show shapes\n 3.Print surfaces\n");
        printf("Make a choice:\n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1: insert_shape();
                    break;
            case 2: show_shapes();
                    break;
            case 3: print_surface();
            
        }
    }
    return 0;
}