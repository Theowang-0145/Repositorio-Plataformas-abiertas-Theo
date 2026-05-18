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
    int base_1, exp_1;  // se declaran las varibales que se van a ingresar por el usuario

    do {                                //inicio del cilo do-while

      printf("Ingrese una base: ");
        scanf("%d", &base_1);

        printf("Ingrese un exponente: ");
        scanf("%d", &exp_1);  

        if (( exp_1 < 0) || (base_1 == 0)) {                //validacion del ingreso por teclado
            printf("Opciones invalidas, la base no debe ser cero y el exponente debe ser mayor que 0 \n");
        }

    } while (( exp_1 < 0) || (base_1 == 0));        //fin ciclo do-while

    printf("%d^%d = %d\n", base_1, exp_1, potencia (base_1, exp_1));
    return 0;
}