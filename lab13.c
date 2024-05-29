#include <stdio.h>
#include <stdlib.h>

void countWays(int coins[], int n, int amount, int **memo, int *combination, int combSize) {
  
    if (amount == 0) {
        for (int i = 0; i < combSize; i++) {
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }

    if (amount < 0 || n <= 0) {
        return;
    }

    if (memo[n][amount] != -1) {
        return;
    }

    combination[combSize] = coins[n-1];
    countWays(coins, n, amount - coins[n-1], memo, combination, combSize + 1);

    countWays(coins, n-1, amount, memo, combination, combSize);

    memo[n][amount] = 1;
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

    int **memo = (int **)malloc((n+1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        memo[i] = (int *)malloc((amount+1) * sizeof(int));
        for (int j = 0; j <= amount; j++) {
            memo[i][j] = -1;
        }
    }

    int *combination = (int *)malloc((amount+1) * sizeof(int));

    printf("Ways to make change for %d:\n", amount);
    countWays(coins, n, amount, memo, combination, 0);

    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    free(combination);

    return 0;
}
