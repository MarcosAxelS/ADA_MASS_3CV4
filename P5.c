#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THRESHOLD 32

int** alloc_matrix(int n) {
    int** m = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        m[i] = calloc(n, sizeof(int));
    }
    return m;
}

void free_matrix(int** m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
}

void matrix_op(int** a, int** b, int** res, int n, int is_add) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = is_add ? (a[i][j] + b[i][j]) : (a[i][j] - b[i][j]);
        }
    }
}

void trad_mult(int** a, int** b, int** c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void dac_mult(int** a, int** b, int** c, int n) {
    if (n <= THRESHOLD) {
        trad_mult(a, b, c, n);
        return;
    }
    int m = n / 2;
    int **a11 = alloc_matrix(m), **a12 = alloc_matrix(m), **a21 = alloc_matrix(m), **a22 = alloc_matrix(m);
    int **b11 = alloc_matrix(m), **b12 = alloc_matrix(m), **b21 = alloc_matrix(m), **b22 = alloc_matrix(m);
    int **c11 = alloc_matrix(m), **c12 = alloc_matrix(m), **c21 = alloc_matrix(m), **c22 = alloc_matrix(m);
    int **t1 = alloc_matrix(m), **t2 = alloc_matrix(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a11[i][j] = a[i][j]; a12[i][j] = a[i][j + m];
            a21[i][j] = a[i + m][j]; a22[i][j] = a[i + m][j + m];
            b11[i][j] = b[i][j]; b12[i][j] = b[i][j + m];
            b21[i][j] = b[i + m][j]; b22[i][j] = b[i + m][j + m];
        }
    }

    dac_mult(a11, b11, t1, m); dac_mult(a12, b21, t2, m); matrix_op(t1, t2, c11, m, 1);
    dac_mult(a11, b12, t1, m); dac_mult(a12, b22, t2, m); matrix_op(t1, t2, c12, m, 1);
    dac_mult(a21, b11, t1, m); dac_mult(a22, b21, t2, m); matrix_op(t1, t2, c21, m, 1);
    dac_mult(a21, b12, t1, m); dac_mult(a22, b22, t2, m); matrix_op(t1, t2, c22, m, 1);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = c11[i][j]; c[i][j + m] = c12[i][j];
            c[i + m][j] = c21[i][j]; c[i + m][j + m] = c22[i][j];
        }
    }
    free_matrix(a11, m); free_matrix(a12, m); free_matrix(a21, m); free_matrix(a22, m);
    free_matrix(b11, m); free_matrix(b12, m); free_matrix(b21, m); free_matrix(b22, m);
    free_matrix(c11, m); free_matrix(c12, m); free_matrix(c21, m); free_matrix(c22, m);
    free_matrix(t1, m); free_matrix(t2, m);
}

void strassen_mult(int** a, int** b, int** c, int n) {
    if (n <= THRESHOLD) {
        trad_mult(a, b, c, n);
        return;
    }
    int m = n / 2;
    int **a11 = alloc_matrix(m), **a12 = alloc_matrix(m), **a21 = alloc_matrix(m), **a22 = alloc_matrix(m);
    int **b11 = alloc_matrix(m), **b12 = alloc_matrix(m), **b21 = alloc_matrix(m), **b22 = alloc_matrix(m);
    int **m1 = alloc_matrix(m), **m2 = alloc_matrix(m), **m3 = alloc_matrix(m), **m4 = alloc_matrix(m);
    int **m5 = alloc_matrix(m), **m6 = alloc_matrix(m), **m7 = alloc_matrix(m);
    int **t1 = alloc_matrix(m), **t2 = alloc_matrix(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a11[i][j] = a[i][j]; a12[i][j] = a[i][j + m];
            a21[i][j] = a[i + m][j]; a22[i][j] = a[i + m][j + m];
            b11[i][j] = b[i][j]; b12[i][j] = b[i][j + m];
            b21[i][j] = b[i + m][j]; b22[i][j] = b[i + m][j + m];
        }
    }

    matrix_op(a11, a22, t1, m, 1); matrix_op(b11, b22, t2, m, 1); strassen_mult(t1, t2, m1, m);
    matrix_op(a21, a22, t1, m, 1); strassen_mult(t1, b11, m2, m);
    matrix_op(b12, b22, t2, m, 0); strassen_mult(a11, t2, m3, m);
    matrix_op(b21, b11, t2, m, 0); strassen_mult(a22, t2, m4, m);
    matrix_op(a11, a12, t1, m, 1); strassen_mult(t1, b22, m5, m);
    matrix_op(a21, a11, t1, m, 0); matrix_op(b11, b12, t2, m, 1); strassen_mult(t1, t2, m6, m);
    matrix_op(a12, a22, t1, m, 0); matrix_op(b21, b22, t2, m, 1); strassen_mult(t1, t2, m7, m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];
            c[i][j + m] = m3[i][j] + m5[i][j];
            c[i + m][j] = m2[i][j] + m4[i][j];
            c[i + m][j + m] = m1[i][j] - m2[i][j] + m3[i][j] + m6[i][j];
        }
    }
    free_matrix(a11, m); free_matrix(a12, m); free_matrix(a21, m); free_matrix(a22, m);
    free_matrix(b11, m); free_matrix(b12, m); free_matrix(b21, m); free_matrix(b22, m);
    free_matrix(m1, m); free_matrix(m2, m); free_matrix(m3, m); free_matrix(m4, m);
    free_matrix(m5, m); free_matrix(m6, m); free_matrix(m7, m);
    free_matrix(t1, m); free_matrix(t2, m);
}

int main() {
    int n, opt;
    printf("Ingrese el tamaño de la matriz (potencia de 2): ");
    scanf("%d", &n);
    printf("Seleccione el metodo:\n1. Tradicional\n2. Divide y Venceras\n3. Strassen\nOpcion: ");
    scanf("%d", &opt);

    srand(time(NULL));
    int **a = alloc_matrix(n);
    int **b = alloc_matrix(n);
    int **c = alloc_matrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }

    clock_t start_t = clock();
    switch (opt) {
        case 1: trad_mult(a, b, c, n); break;
        case 2: dac_mult(a, b, c, n); break;
        case 3: strassen_mult(a, b, c, n); break;
        default: printf("Opcion no valida.\n"); return 1;
    }
    clock_t end_t = clock();

    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecucion fue: %.6f segundos\n", total_t);

    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(c, n);
    return 0;
}