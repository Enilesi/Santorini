#include<stdio.h>
#include<stdlib.h>
void err( char *mess)
{
    printf("%s",mess);
     exit(-1);
}

int valid(char v[],int k)
{
    for(int i=0;i<k-1;i++)
    if(v[i]==v[k]) return 0;
    return 1;
}

void printing(char v[], int n)
{
    for(int i=0;i<n;i++)
            {
                printf("%c",v[i]);
            }
}


void back (char v[], char voc[],int n, int k)
{
    if(n>5||n<1)
    {
        err("n err");
    }
    if(k==n)
    {
        printing(v,n);
        printf(("\n"));
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            v[k]=voc[i];
            if(valid(v,k))
            {
                back(v,voc,n,k+1);
            }
        }
    }


}
int main()
{
    int n;
       if(scanf("%d",&n)!=1)
    {
        err("scanf err");
    }
    char v[n];
    char voc[]={'a','e','i','o','u'};
    back(v,voc,n,0);
    return 0;
}