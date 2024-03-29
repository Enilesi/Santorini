#include<stdio.h>


int valid(int v[],int k)
{
    for(int i=1;i<k;i++)
    if(v[i]==v[k]) return 0;
    return 1;
}

void printing(int v[], int n)
{
    for(int i=0;i<n;i++)
            {
                printf("%d",v[i]);
            }
}
void err( char *mess)
{
    printf("%s",mess);
}
void back (int v[], int n, int k)
{
    if(k==n)
    {
        printing(v,n);
        printf(("\n"));
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            v[k]=i;
            if(valid(v,k))
            {
                back(v,n,k+1);
            }
        }
    }


}
int main()
{
    int n;
 

    int v[n];
    back(v,n,0);
    return 0;
}