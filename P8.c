#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 31

int memo[MAX_LEN][MAX_LEN][MAX_LEN];

bool solve_scramble(const char* s1, const char* s2, int i, int j, int len) {
    if (memo[len][i][j] != -1) {
        return memo[len][i][j];
    }
    if (strncmp(s1 + i, s2 + j, len) == 0) {
        return memo[len][i][j] = 1;
    }

    int count[26] = {0};
    for (int k = 0; k < len; k++) {
        count[s1[i + k] - 'a']++;
        count[s2[j + k] - 'a']--;
    }
    for (int k = 0; k < 26; k++) {
        if (count[k] != 0) {
            return memo[len][i][j] = 0;
        }
    }

    for (int k = 1; k < len; k++) {
        if (solve_scramble(s1, s2, i, j, k) && solve_scramble(s1, s2, i + k, j + k, len - k)) {
            return memo[len][i][j] = 1;
        }
        if (solve_scramble(s1, s2, i, j + len - k, k) && solve_scramble(s1, s2, i + k, j, len - k)) {
            return memo[len][i][j] = 1;
        }
    }

    return memo[len][i][j] = 0;
}

bool check_scramble(const char* s1, const char* s2) {
    int n = strlen(s1);
    if (n != (int)strlen(s2)) {
        return false;
    }
    if (n == 0) {
        return true;
    }
    memset(memo, -1, sizeof(memo));
    return solve_scramble(s1, s2, 0, 0, n);
}

int main() {
    char s1[MAX_LEN];
    char s2[MAX_LEN];

    printf("--- Verificador de Cadenas Mezcladas (Scrambled String) ---\n");
    
    printf("Ingrese la primera cadena (s1): ");
    scanf("%30s", s1);

    printf("Ingrese la segunda cadena (s2): ");
    scanf("%30s", s2);

    if (check_scramble(s1, s2)) {
        printf("\nResultado: Verdadero. La cadena '%s' SI es una mezcla posible de '%s'.\n", s2, s1);
    } else {
        printf("\nResultado: Falso. La cadena '%s' NO es una mezcla posible de '%s'.\n", s2, s1);
    }

    return 0;
}