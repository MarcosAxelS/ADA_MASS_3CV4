#include <stdio.h>
#include <stdlib.h>

int trap_water(int* height, int size) {
    if (size <= 2) {
        return 0;
    }

    int left = 0;
    int right = size - 1;
    int max_left = 0;
    int max_right = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= max_left) {
                max_left = height[left];
            } else {
                water += max_left - height[left];
            }
            left++;
        } else {
            if (height[right] >= max_right) {
                max_right = height[right];
            } else {
                water += max_right - height[right];
            }
            right--;
        }
    }
    return water;
}

int main() {
    int n;
    int* height;

    printf("--- Calculadora de Agua de Lluvia Atrapada ---\n");
    printf("Ingrese el numero de elementos en el mapa de elevacion (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: El numero de elementos debe ser un entero positivo.\n");
        return 1;
    }

    height = (int*)malloc(n * sizeof(int));
    if (height == NULL) {
        printf("Error critico: No se pudo asignar memoria para el arreglo.\n");
        return 1;
    }

    printf("Ahora, ingrese los %d valores de altura, separados por un espacio:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }

    int total_water = trap_water(height, n);

    printf("\nResultado: La cantidad total de agua atrapada es de %d unidades.\n", total_water);

    free(height);

    return 0;
}