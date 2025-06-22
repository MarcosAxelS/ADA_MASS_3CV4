#include <stdio.h>

#define N 4
#define W 4

int main() {
    int val[N] = {1500, 2000, 3000, 2000}; // G, L, S, I
    int wt[N] = {1, 3, 4, 1};             // G, L, S, I
    char *nms[N] = {"Guitarra", "Laptop", "Estéreo", "iPhone"};
    int dp[N+1][W+1];

    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = (val[i-1] + dp[i-1][w - wt[i-1]] > dp[i-1][w]) ?
                           val[i-1] + dp[i-1][w - wt[i-1]] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    printf("Valor máximo: $%d\n", dp[N][W]);
    printf("Objetos seleccionados:\n");

    int w = W;
    for (int i = N; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("- %s\n", nms[i-1]);
            w -= wt[i-1];
        }
    }

    return 0;
}