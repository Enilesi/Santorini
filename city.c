#include<stdio.h>
#define N 5
#define INT_MAX 10000000
int findNextCity(int CurrentCity,int visited[N], int graph[N][N])
{
    int minDistance=INT_MAX;
    int nextCity=-1;
    for(int i=0;i<N;i++)
    {
        if(!visited[i] && graph[CurrentCity][i] && graph[CurrentCity][i]<minDistance)
        {
            minDistance=graph[CurrentCity][i];
            nextCity=i;
        }
    }
    return nextCity;
}
int main()
{
    int graph[N][N]={ {0,174,315,634,544},
                          {174,0,152,0,595},
                          {315,152,0,393,449},
                          {634,544,393,0,388},
                          {544,595,449,388,0}
    };
    int startCity;
    printf("GREEDY TSP PROBLEM\n0-Timisoara\n1-Oradea\n2-Cluj-Napoca\n3-Iasi\n4-Bucuresti\n\nSelect a city: ");
    scanf("%d",&startCity);
    int visited[N]={0};
    int totalDistance=0;
    int tour[N+1];
    visited[startCity]=1;
    tour[0]=startCity;
    for(int i=1;i<N;i++)
    {
        int nextCity=findNextCity(startCity,visited,graph);
        if(nextCity==-1)
        {
            printf("No complete tour possible!\n");
            return -1;
        }
        visited[nextCity]=1;
        totalDistance+=graph[startCity][nextCity];
        tour[i]=nextCity;
        startCity=nextCity;
    }
    totalDistance+=graph[startCity][tour[0]];
    tour[N]=tour[0];
    printf("Tour:");
    for(int i=0;i<=N;i++)
    {
        printf("%d-",tour[i]);
    }
    printf("\n");
    printf("Total distance: %d",totalDistance);
    return 0;
}