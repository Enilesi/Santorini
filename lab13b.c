#include<stdio.h>


unsigned long int fib( unsigned long int n ) 
{
	long int f[n+1] ;
	unsigned int i ;
	f[0]=0 ;
	f[1]=1 ;
	for(i=2;i<=n;i++) 
		f[i]=-1;
	if(n>2) 
		{
		for(i=2;i<=n;i++) 
			{
			if(f[i]<0)f[i]=f[i-1]+f[i-2];
			}
		}
	return( unsigned long int ) f[n] ;
}

long int F[1000];

unsigned long int fibMemoizationRec(unsigned long int n) {
    if (F[n] == -1) {
        if (n == 0) F[n] = 0;
        else if (n == 1) F[n] = 1;
        else F[n] = fibMemoizationRec(n - 1) + fibMemoizationRec(n - 2);
    }
    return F[n];
}

unsigned long int fibMemoization(unsigned long int n) {
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i <= n; i++) {
        F[i] = -1;
    }
    return fibMemoizationRec(n);
}

unsigned long int fibBottomUpDP(unsigned long int n) {
    F[0] = 0;
    F[1] = 1;
    for(int i=2;i<=n;i++) 
			{
			if(F[i]<0)F[i]=F[i-1]+F[i-2];
			}
    return F[n];
}

int main () {
    printf("fib(100) = %lu\n", fib(100));
    printf("fib(3) = %lu\n", fib(3));
    printf("fib(5) = %lu\n", fib(5));
    printf("fib(11) = %lu\n", fib(11));
    
    printf("fibMemoization(100) = %lu\n", fibMemoization(100));

	printf("fibBottomUP(100) = %lu\n", fibBottomUpDP(100));

    return 0;
}

