#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int contar_unos_fila(int m[][SIZE], int fila);
int contar_unos_columna(int m[][SIZE], int col);


int es_identidad(int m[][SIZE]) {
    int i, j;  
    int flag = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {

            if ((i == j) && (m[i][j] != 1)) {
                flag++;
            }

            if ((i != j) && (m[i][j] != 0)) {
                flag++;
            }
        }
    }
    if (flag > 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int tiene_fila_completa(int m[][SIZE]) {
    int i, j, contador; 
    
    for (i = 0; i < SIZE; i++) {
        contador = 0;
        for (j = 0; j < SIZE; j++) {

            if (m[i][j] == 1){
                contador++;
            }
        }
        
        if (contador == SIZE) {
            printf("Si hay al menos una fila de unos \n");
            return 1;
        }
    }

    printf("No tieneal menos una fila entera de unos \n");
    return 0;
}

int tiene_columna_completa(int m[][SIZE]) {
    int i, j, contador; 
    
    for (j = 0; j < SIZE; j++) {
        contador = 0;
        for (i = 0; i < SIZE; i++) {

            if (m[i][j] == 1){
                contador++;
            }

        }

        if (contador == SIZE) {
            printf("Si hay al menos una columna de unos \n");
            return 1;
        }
    }

    printf("No tiene al menos una columna entera de unos \n");
    return 0;
}

int main(void) {
    int validacion;
    char positivo[] = "SI";
    char negativo[] = "NO";
    int m[SIZE][SIZE] = {
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1}
    };

    validacion = es_identidad(m);
    printf("Es matriz identidad:%s \n", (validacion == 1) ? positivo : negativo);
    tiene_columna_completa(m);
    tiene_fila_completa(m);

    return 0; 
}