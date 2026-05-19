#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
/*
=================================================== SECCION DE FUNCIONES ================================================
*/
int contar_unos_fila(int m[][SIZE], int fila) {         //Esta funcion es utilizada para contar los unos de las filas
    
    int contador, j;

    contador = 0;
    for (j = 0; j < SIZE; j++) {           //utiliza parametros de la propia matriz y una variable de fila, la cual se utiliza
                                           //para ir recorriendo la matriz por columnas

        if (m[fila][j] == 1){
            contador++;                    //este contador se utiliza para verificar la cantidad de veces que se repite el numero 1
        }                                  //dentro de una misma fila. Este mismo valor se retorna para luego ser evaluado
    }
    return contador;
}

int contar_unos_columna(int m[][SIZE], int col){        //por otro lado esta la funcion para contar los unos de las columnas

    int contador, i;                //aca se utiliza la misma logica que la de antes 

    contador = 0;
    for (i = 0; i < SIZE; i++) {

        if (m[i][col] == 1){        //se plantea un contador el cual se utiliza para verificar la cantidad de apariciones dle numero 1
            contador++;             //en la serie de columnas. Luego se retorna y se evalua
        }
    }
    return contador;
}

int es_identidad(int m[][SIZE]) {               //la logica de esta funcion es un tanto diferente, pero es para verificar si una matriz
    int i, j;                                   //es la matriz identidad.
    int flag = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {        //por un lado se itera tanto en i y en j para recorrer toda la matriz 

            if ((i == j) && (m[i][j] != 1)) {   //y se plantea que en los casos donde las posiciones sean iguales, no puede ser diferente a 1,
                flag++;                         //puesto que sino, se suma a un tipo contador quee ya no se cumple la forma asociada de la matriz identidad.
            }           //idea intuitiva >> se levanta una banderita

            if ((i != j) && (m[i][j] != 0)) {   //la misma idea se aplica pero para las posiciones diferentes de i y jota, las cuales NO pueden 
                flag++;                         //ser diferentes a 0. 
            }
        }
    }
    if (flag > 0) {         //por ultimo se retornan valores segun los dos casos principales, estos se evaluan al final
        return 0;
    }
    else {
        return 1;
    }
}

int tiene_fila_completa(int m[][SIZE]) {        //estas funciones son para verificar si en una fila sola hay solo unos
    int i, contador;            //cabe recalcar que se pudo haber hecho todo en esta funcion sin embargo se ordena mejor en dos diferentes
    
    for (i = 0; i < SIZE; i++) {        
        contador = contar_unos_fila(m,i);       //se llama a la funcion de contar unos por filas
        if (contador == SIZE) {
            return 1;       //retorna un valor diferente dependiendo del caso. Estos retornos son adquiridos por otras variables para ser evaluados.
        }
    }
    return 0;
}

int tiene_columna_completa(int m[][SIZE]) {     //lo mismo ocurre con el caso de las columnas
    int j, contador; 
    
    for (j = 0; j < SIZE; j++) {
        contador = contar_unos_columna(m,j);        //se llama a la funcion de contar unos por columnas
        if (contador == SIZE) {
            return 1;
        }                       //igual retorna los dos valores para ser evaluados despues
    }
    return 0;
}

void imprimir_matriz (int m[][SIZE]) {       //esta funcion permite imprimir la matriz por medio de iteraciones
    int i, j;
    
    printf("Matriz Ingresada: \n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {        //la idea es mantener una fila fija mientras se iteran columnas y se van imprimiendo
            printf("%d ", m[i][j]);
        }
        printf("\n");       //caber recalcar este cambio de linea por cada salto de fila
    
    }
    

}

void rellenar_aleatoria (int m[][SIZE]){        //esta funcion recibe el parametro de una matriz vacia y la introduce en una matriz m local
    int i, j; 
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            m[i][j] = rand() % 2;       //cada fila y columna se llena con un numero del 0 al 1 de manera aleatoria
        }                               //Y como es una funcion con operaciones se puede utilizar void
    }
}

/* 
====================================================== SECCION MAIN ========================================================
*/

int main(void) {
    int v0, v1, v2;
    char positivo[] = "SI";         //varibales para evaluar resultado de analisis de matrices
    char negativo[] = "NO";
    int m[SIZE][SIZE] = {
        {1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0}, 
        {0, 0, 1, 1, 0}
    };
    int m_aleatoria [SIZE][SIZE];
    srand(time(NULL));

 /* 
# Llamado de funciones #
*/


/* 
# Llamado de funciones para matriz elegida por el programa #
*/
    imprimir_matriz(m);
    v0 = es_identidad(m);
    printf("Es matriz identidad:%s \n", (v0 == 1) ? positivo : negativo);        //evaluacion final 
    v1 = tiene_columna_completa(m);
    printf("Tiene columna completa de unos:%s \n", (v1 == 1) ? positivo : negativo);
    v2 = tiene_fila_completa(m);
    printf("Tiene fila completa de unos:%s \n", (v2 == 1) ? positivo : negativo);


/* 
# Llamado de funciones para matriz aleatoria #
*/
    printf("\n");
    rellenar_aleatoria(m_aleatoria);                    
    imprimir_matriz(m_aleatoria);
    v0 = es_identidad(m_aleatoria);
    printf("Es matriz identidad:%s \n", (v0 == 1) ? positivo : negativo);        //evaluacion final 
    v1 = tiene_columna_completa(m_aleatoria);
    printf("Tiene columna completa de unos:%s \n", (v1 == 1) ? positivo : negativo);
    v2 = tiene_fila_completa(m_aleatoria);                                              //se pueden utilizar las mismas variables pues solo se
    printf("Tiene fila completa de unos:%s \n", (v2 == 1) ? positivo : negativo);       //utilizan para un condicional y pueden ser reescritas nuevamente

    return 0; 
}