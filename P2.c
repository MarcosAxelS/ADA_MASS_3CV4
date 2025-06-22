#include <stdio.h>
#include <stdlib.h>

int divide (int a, int b){

    int div=0, aux=abs(b);
    if (b==0){
        printf("La division entre cero no esta permitida.\n");
        return 0;

    }
    if ((a<0) != (b<0)){
        a = abs(a);
        b = abs(b);

        while (a>=b){
            b = b + aux;
            div++;
        }
        div=0-div;
    }else{
        a = abs(a);
        b = abs(b);
        
        while (a>=b){
            b = b + aux;
            div++;
        }
    }
    printf("El resultado de la division es: %d\n", div);
}

void main (){
    int dor=0, ddo=0;
    printf("Inserte el valor del dividendo:\n");
    scanf("%d",&ddo);
    printf("Inserte el valor del divisor:\n");
    scanf("%d", &dor);
    divide(ddo, dor);

}
