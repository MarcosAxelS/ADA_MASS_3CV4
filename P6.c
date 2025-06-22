#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int* gen_filtered_fib(int k_val, int* size) {
    int cap = 100;
    int* seq = (int*)malloc(cap * sizeof(int));
    long long a = 0, b = 1;
    int idx = 1;
    *size = 0;

    while (a <= k_val) {
        if (!is_prime(idx)) {
            if (*size >= cap) {
                cap *= 2;
                seq = (int*)realloc(seq, cap * sizeof(int));
            }
            seq[(*size)++] = (int)a;
        }
        long long temp = a + b;
        a = b;
        b = temp;
        idx++;
    }
    return seq;
}

int find_min_terms(int* seq, int size, int k_val, int* selected) {
    int count = 0;
    int original_k = k_val;

    for (int i = size - 1; i >= 0; i--) {
        if (seq[i] <= k_val) {
            selected[count++] = seq[i];
            k_val -= seq[i];
        }
    }

    if (k_val == 0) {
        return count;
    }
    
    return -1;
}

int main() {
    int day = 11, month = 6, year = 2002;
    int K = day * 100 + month * 10 + (year % 100);
    printf("Valor de K calculado: %d\n\n", K);

    int size;
    int* fib_seq = gen_filtered_fib(K, &size);

    printf("Secuencia de Fibonacci filtrada (sin terminos en posiciones primas):\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", fib_seq[i]);
    }
    printf("\n\n");

    int selected_terms[100];
    int terms_count = find_min_terms(fib_seq, size, K, selected_terms);

    if (terms_count != -1) {
        printf("Suma optima encontrada con %d terminos:\n", terms_count);
        for (int i = 0; i < terms_count; i++) {
            printf("%d%s", selected_terms[i], (i == terms_count - 1) ? "" : " + ");
        }
        printf(" = %d\n", K);
    } else {
        printf("Con el algoritmo voraz especificado, no se encontro una combinacion exacta para K = %d.\n", K);
    }

    free(fib_seq);
    return 0;
}
