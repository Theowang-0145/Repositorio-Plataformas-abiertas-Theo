#include <stdio.h>
#include <stdlib.h>

/*
Por la complicidad de manejar archivos y la lectura de los mismos este primer avance consta en solamente entender como se lee el archivo para poder manejarlo de manera correcta
*/

/*
void apply_threshold(unsigned char *pixels, int total, int threshold) 
unsigned char *make_negative (unsigned char *pixels, int total)
void write_pgm(const chat *filename, unsigned chat *pixels, int width, int height, int max_val)
void print_stats (unsigned char *original, unsigned char *thresholded, int total)
*/

unsigned char *read_pgm(const char *filename, int *width, int* height, int *max_val){   //esta funcion es unicamente para leer el archivo input

    unsigned char *pixels = NULL;           //lee el archivo input.pgm (debe estar en la misma carpeta/directorio) y lo va escaneando por partes
    FILE *archivo = fopen(filename, "r");

    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
        return NULL;
    }

    char formato[10];
    fscanf(archivo,"%2s", formato);
    fscanf(archivo, "%d %d", width, height );      //sin embargo hay que ser muy cuidadosos con el cursor y demas, pues es directamente una copia del archivo
    fscanf(archivo, "%d", max_val );

    int tot_datos = (*width) * (*height);
    pixels = malloc(tot_datos * sizeof(unsigned char));     //a la hora de analizar los pixeles por facilidad se analizan en un arreglo lineal del tamano del ancho por alto

    for (int i = 0; i<tot_datos; i++){
        fscanf(archivo, "%hhu", pixels +i);         //de esta forma cada dato se copia directamente al arreglo lineal para poder ser analizados despues 
    }

    fclose(archivo);        //por ultimo se cierra el archivo y se retorna el puntero al arreglo de memoria dinamica
    return pixels;          //cabe recalcar que las demas variables son cambiadas directamente por punteros 

}

int main (void){ 
    int width, height, max_val;
    char filename [100];        //aca se inicializan todas las variables, entre ellas la variable del nombre del archivo
    unsigned char *pixels = NULL;       //se inicializa el puntero
    //unsigned char *negative = NULL; 
    
    printf("Ingrese el nombre dle archivo (<archivo>.pgm) : ");
    scanf("%99s", filename);

    pixels = read_pgm(filename, &width, &height, &max_val); //aca se iguala directamente con la funcion pues se retorna un puntero directamente


    printf("Ancho: %d  \n", width);     //en este caso se utilizaron estos prints para poder verificar que el escaneo funciono de manera correcta
    printf("Alto: %d  \n", height);
    printf("Max val: %d \n", max_val);

    for (int i = 0; i < 8; i++) {
    printf("%hhu ", *(pixels + i));
    }
    return 0;
}