#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long calculate_chemistry(int* skill, int size) {
    long long total = 0;
    for (int i = 0; i < size; i++) {
        total += skill[i];
    }

    int teams = size / 2;
    if (total % teams != 0) {
        return -1;
    }

    long long target = total / teams;
    qsort(skill, size, sizeof(int), compare);

    long long chem_sum = 0;
    int left = 0;
    int right = size - 1;

    while (left < right) {
        if (skill[left] + skill[right] != target) {
            return -1;
        }
        chem_sum += (long long)skill[left] * skill[right];
        left++;
        right--;
    }

    return chem_sum;
}

int main() {
    int size;
    printf("Ingrese el tamaño del arreglo (debe ser un numero par): ");
    scanf("%d", &size);

    if (size % 2 != 0 || size <= 0) {
        printf("El tamaño del arreglo debe ser un numero par y positivo.\n");
        return 1;
    }

    int* skill = (int*)malloc(size * sizeof(int));
    if (skill == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("Ingrese los valores de habilidad:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &skill[i]);
    }

    long long result = calculate_chemistry(skill, size);

    if (result == -1) {
        printf("Resultado: -1 (No se pueden formar equipos con suma de habilidad igual)\n");
    } else {
        printf("La quimica total de los equipos es: %lld\n", result);
    }

    free(skill);
    return 0;
}