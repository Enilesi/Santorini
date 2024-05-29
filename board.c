#include <stdio.h>
#include <stdlib.h>

int countWaysMemo(int coins[], int n, int amount, int memo[][amount+1]) {
    if (amount == 0) return 1;
    if (amount < 0 || n <= 0) return 0;

    if (memo[n][amount] != -1) return memo[n][amount];

    memo[n][amount] = countWaysMemo(coins, n-1, amount, memo) + countWaysMemo(coins, n, amount - coins[n-1], memo);

    return memo[n][amount];
}

int main() {
    int n, amount;

    printf("Enter the number of different coins: ");
    scanf("%d", &n);

    int coins[n];
    
    printf("Enter the values of the coins: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter the amount: ");
    scanf("%d", &amount);

    int memo[n+1][amount+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= amount; j++) {
            memo[i][j] = -1;
        }
    }


    int ways = countWaysMemo(coins, n, amount, memo);
    printf("Number of ways to make change for %d: %d\n", amount, ways);



    return 0;
}
