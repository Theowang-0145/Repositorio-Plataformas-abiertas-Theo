#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
este primer avance va a constar en pedirle al usuario un tamano de una matriz cuadrada y poder hacerle un espacio de punteros 
de manera que esten seguidos uno de otro y asi se pueda obtener un puntero doble que tenga ese arreglo de punteros. 
seguidamente llenarlos e imprimirlos en pantalla. Tambien imprimir la memoria de cada puntero, para demostrar que estan seguidos
*/

/*
void findLargestLine(int **matriz, int size, int *result){}

*/

/*
=================================================== SECCION DE FUNCIONES ================================================
*/
void allocateMatriz (int ***matriz, int size){
    *matriz = malloc(size * sizeof(int *)); //esto hace size espacios de tamano de punteros de enteros, esto pues cada puntero va a apuntar a una fila de la matriz
    
    for(int i = 0; i<size; i++){

        *(*matriz + i) = malloc(size * sizeof(int)); //y esta funcion genera por cada puntero del array, un array de size espacios para cada int
    
    }                                                  //se debe de tomar en cuenta que no es un arreglo lineal, por lo que en la funcion que queda debe hacerse un arreglo con todos estos numeros y ahi recorrerlo con punteros
}

void fillMatriz(int **matriz, int size){        //funcion para rellenar la matriz de unos

    for (int i = 0; i<size; i++){       //cabe recalcar que se desrefencia una vez por cada i y luego otra vez por cada j, puesto que se busca que cada direccion a la que apunte cada puntero dentro del array sea un 0 o un 1
        for (int j = 0; j<size; j++){

            *(*(matriz + i) + j) = (rand() % 10) < 7;       //se utiliza rand para generar datos aleatorios entre 1 y 0, en este caso se cambia un poco la probabilidad para que aparezcan mas 1's
        }
    }
}

void printMatriz (int **matriz, int size){  //esta funcion recibe un puntero doble, el cual es el mismo arreglo de punteros el cual van a ser impresos uno a uno 
    printf("Matriz (%dx%d):\n", size, size);    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {       
            printf("%d", *(*(matriz + i) + j)); //aca se desreferencia la matriz como tal. primero en un puntero con una posicion de fila, y luego la misma posicion 
        }                                       //fila de ese mismo puntero.
        printf("\n");
    }
}

void freeMatriz (int **matriz, int size){  //esta funcion es para liberar el espacio reservado por cada puntero, ya sea doble y unico
    for (int i = 0; i < size; i++){        //en primera instancia libera la memoria guardada por cada puntero, es decir un array de size int's
        free(*(matriz + i));               //en segundo lugar un libera la segunda 
    }
    free(matriz);
}

/*
=================================================== SECCION DE MAIN =====================================================
*/

int main (void){
    int size;
    int **matriz = NULL; //se inicializa el puntero en NULL pues se necesita rellenar despues segun lo que quiera el usuario
    srand(time(NULL));

    printf("Ingrese el tamano de la matriz cuadrada a analizar:");
    scanf("%d", &size);
    printf("\n"); 

    allocateMatriz(&matriz,size); //como la matriz va a ser cambiada desde un puntero no se necesita retornar nada. Cabe aclarar que esta funcion lo que realiza es guardarle un espacio de memoria a ese puntero, el cual va a ser un array de n punteros
    fillMatriz(matriz, size); //las funciones siguientes reciben la matriz como tal, es decir el puntero doble, pues se necesita leer, llenar, o analizar, no cambiar nada de ella
    printMatriz(matriz,size); 
    freeMatriz(matriz,size);
}
