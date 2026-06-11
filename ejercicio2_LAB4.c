#include <stdio.h>
#include <stdlib.h>

/*
Este segundo avance es mucho mas manejable pues ya se trabaja con el puntero de pixels, entonces consta de 
aplicar un umbral ingresado por el usuario y luego sacar el negativo. el tercer avance ya va a ser sobre la creacion de las imagenes y las stats
*/

/*
void write_pgm(const chat *filename, unsigned chat *pixels, int width, int height, int max_val)
void print_stats (unsigned char *original, unsigned char *thresholded, int total)
*/
unsigned char *make_negative (unsigned char *pixels, int total){


    unsigned char *negative = malloc(total * sizeof(unsigned char));

    if (negative == NULL) {     //verificacion para el puntero negative
        printf("Error: no se pudo reservar memoria para el puntero negativo.\n");
        return NULL;
    }

    for (int i = 0; i < total; i++) {       //condicion de negativa el cual cambia todos los valores del umbral al inverso por decirlo asi
        *(negative + i) = 255 - *(pixels + i);
    }

    return negative;    //retorna negative como puntero para ser recibido por el otro puntero en main
}

void apply_threshold(unsigned char *pixels, int total_datos, int threshold) {
    
    //la idea aca es leer dato por dato los pixeles aplicando la condicion del umbral

    for (int i = 0; i<total_datos; i++){
        if (*(pixels + i) >= threshold){    //aca se plantea la condicion del umbral y se van cambiando los valores de pixels uno por uno hasta el total de datos
            *(pixels + i) = 255; 
        }
        else {
            *(pixels + i) = 0; 
        }
    }
}

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

    if (pixels == NULL) {       //esta es la verificacion para la memoria dinamica del puntero pixels
        printf("Error: no se pudo reservar memoria para el puntero de pixels.\n");
        return NULL;
    }

    for (int i = 0; i<tot_datos; i++){
        fscanf(archivo, "%hhu", pixels +i);         //de esta forma cada dato se copia directamente al arreglo lineal para poder ser analizados despues 
    }

    fclose(archivo);        //por ultimo se cierra el archivo y se retorna el puntero al arreglo de memoria dinamica
    return pixels;          //cabe recalcar que las demas variables son cambiadas directamente por punteros 

}

int main (void){ 
    int width, height, max_val, threshold, total_datos;
    char filename [100];        //aca se inicializan todas las variables, entre ellas la variable del nombre del archivo
    unsigned char *pixels = NULL;       //se inicializa el puntero
    unsigned char *negative = NULL; 

    
    
    printf("Ingrese el nombre del archivo (<archivo>.pgm) : ");
    scanf("%99s", filename);

    pixels = read_pgm(filename, &width, &height, &max_val); //aca se iguala directamente con la funcion pues se retorna un puntero directamente
    
    total_datos = width * height; //cabe aclarar que este dato debe ser tomado despues de la funcion read_pgm pues sino los valores no han sido asignados todavia


    printf("Ingrese el umbral: ");
    scanf("%d", &threshold);        //aca se lee el umbral ingresado por el usuario

    apply_threshold(pixels,total_datos,threshold); 
    negative = make_negative(pixels,total_datos);   //se iguala a negative pues retorna un puntero de un array de datos

    for (int k = 0; k<8; k++){
        printf("%hhu ", *(negative +k));        //esto es simplemente una prueba de que el negativo si esta teniendo datos coherentes
    } 
    printf("\n");


    //free(pixels)
    //free(negaive) estos dos se ponen hasta el finak cuando ya no sean utilizados

    return 0;
}