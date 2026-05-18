#include <stdio.h>

int potencia (int base, int exp) {
    
    int resultado = 1;

    while ( exp > 0) {
        resultado = resultado * base;
        exp--;              /* El error anterior fue crear la varibale "exp" la cual 
                            ya fue dada por los parametros de la funcion. 
                            Con el operador x-- se reduce el exponente hasta 0 para terminar el ciclo*/
    }
    return resultado;
}

int main (void) {
    printf("2^8 = %d\n", potencia (2, 8));
    printf("3^4 = %d\n", potencia (3, 4));
    return 0;
}