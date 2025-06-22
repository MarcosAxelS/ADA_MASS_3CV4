#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int n) {
    if (n < 0 || (n % 10 == 0 && n != 0)) {
        return false;
    }

    int rev = 0;
    while (n > rev) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }

    return n == rev || n == rev / 10;
}

int main() {
    int num;
    char choice;

    do {
        printf("Ingresa un numero entero: ");
        scanf("%d", &num);

        if (isPalindrome(num)) {
            printf("%d es un palindromo.\n", num);
        } else {
            printf("%d no es un palindromo.\n", num);
        }

        printf("Quieres verificar otro numero? (s/n): ");
        scanf(" %c", &choice);
        printf("---------------------------\n");

    } while (choice == 's' || choice == 'S');

    return 0;
}