#include <stdio.h>
#include <stdlib.h>

int countWaysGreedy(int coins[], int n, int amount) {
    int count = 0;
    while (amount > 0 && n > 0) {
        if (coins[n - 1] <= amount) {
            int times = amount / coins[n - 1];
            count += times;
            amount -= times * coins[n - 1];
        }
        n--;
    }
    if (amount == 0) return count;
    return -1;
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

    int ways = countWaysGreedy(coins, n, amount);
    if (ways != -1) {
        printf("Number of ways to make change for %d: %d\n", amount, ways);
    } else {
        printf("No solution possible.\n");
    }

    return 0;
}
