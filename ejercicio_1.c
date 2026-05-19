#include <stdio.h>

int es_par (int n) {            //se realiza una funcion especifica para la diferenciacion del resultado 

    if (n % 2 == 0) {
        return 1;
    }
    else { 
        return 0;
    }
}

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
    int base_1, exp_1, resultado, valor;  // se declaran las varibales que se van a ingresar por el usuario

    do {                                //inicio del cilo do-while

      printf("Ingrese una base: ");
        scanf("%d", &base_1);

        printf("Ingrese un exponente: ");
        scanf("%d", &exp_1);  

        if (( exp_1 < 0) || (base_1 == 0)) {                //validacion del ingreso por teclado
            printf("Opciones invalidas, la base no debe ser cero y el exponente debe ser mayor que 0 \n");
        }

    } while (( exp_1 < 0) || (base_1 == 0));        //fin ciclo do-while

    resultado = potencia (base_1, exp_1);           //el return de la funcion de potencia se guarda en una variable de resultado 
                                                    //asi entonces se puede implementar como argumento de la funcion es_par 
    printf("%d^%d = %d \n", base_1, exp_1, resultado);

    valor = es_par(resultado);      //se guarda en una varibale el valor de retorno de la funcion para utilizarla en el condicional
    
    if (valor == 1) {               //se plantea la condicion de par impar de manera que se imprima en pantalla dicho resultado
        printf("El resultado es par \n");
    }
    else {
        printf("El resultado es impar \n");
    }


    return 0;
}