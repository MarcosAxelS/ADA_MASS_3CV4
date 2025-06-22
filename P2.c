#include <stdio.h>
#include <string.h>

#define MAX_COMBS 256 // Máximo de combinaciones para 4 dígitos (4^4)
#define MAX_LEN 5     // Máximo de longitud de dígitos (4) + terminador nulo ('\0')

const char *phone_map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

void backtrack(const char* digits, int idx, char* path, char results[][MAX_LEN], int* count) {
    if (digits[idx] == '\0') {
        strcpy(results[*count], path);
        (*count)++;
        return;
    }

    int digit_val = digits[idx] - '0';
    const char* letters = phone_map[digit_val];

    for (int i = 0; letters[i] != '\0'; i++) {
        path[idx] = letters[i];
        path[idx + 1] = '\0';
        backtrack(digits, idx + 1, path, results, count);
    }
}

void find_combinations(char* digits, char results[][MAX_LEN], int* count) {
    *count = 0;
    if (digits[0] == '\0') {
        return;
    }

    for (int i = 0; digits[i] != '\0'; i++) {
        if (digits[i] < '2' || digits[i] > '9') {
            printf("Error: La entrada contiene digitos invalidos.\n");
            return;
        }
    }

    char path[MAX_LEN] = "";
    backtrack(digits, 0, path, results, count);
}

int main() {
    char digits[MAX_LEN];
    printf("Introduce los digitos (2-9, maximo 4): ");
    scanf("%s", digits);

    if (strlen(digits) > 4) {
        printf("Error: La longitud maxima es de 4 digitos.\n");
        return 1;
    }

    char results[MAX_COMBS][MAX_LEN];
    int count = 0;

    find_combinations(digits, results, &count);

    if (count > 0) {
        printf("Combinaciones posibles:\n");
        for (int i = 0; i < count; i++) {
            printf("%s ", results[i]);
        }
        printf("\n");
    }

    return 0;
}