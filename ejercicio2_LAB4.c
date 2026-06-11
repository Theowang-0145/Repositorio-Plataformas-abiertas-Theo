#include <stdio.h>
#include <stdlib.h>

/*
Ya este ultimo avance es sobre la impresion de los punteros en archivos pgm para comparar los resultados
*/

/*
=================================================== SECCION DE FUNCIONES ================================================
*/

void print_stats (unsigned char *original, unsigned char *thresholded, int total){

    int blanco = 0;
    int negro = 0; 
    int sumatoria = 0; 
    float promedio = 0; 

    for (int i = 0; i<total; i++){
        if (*(thresholded + i) == 0){
            negro++; 
        }
        else{
            blanco++; 
        }
        sumatoria += *(original + i);
    }

    promedio = (float)sumatoria / total;

    printf("Para la umbralizada la cantidad de pixeles blancos son: %d \n", blanco); 
    printf("Para la umbralizada la cantidad de pixeles negros son: %d \n", negro); 
    printf("El promedio de pixeles del arreglo original es: %2.f \n", promedio);

}

void write_pgm(const char *filename, unsigned char *pixels, int width, int height, int max_val){ //esta funcion genera archivos de tipo pgm con todos datos en su interior 

    FILE *archivo = fopen(filename, "w");   //esta funcion crea un archivo con el nombre ingresado
    fprintf(archivo, "P2\n");
    fprintf(archivo, "%d %d\n", width, height); //seguidamente hay que ponerle los datos linea por linea y dejando espaios para cumplir con el formato
    fprintf(archivo, "%d \n", max_val); 

    int a = 0;
    for (int i = 0; i<height; i++){     //se utiliaz un ciclo anidado con height y width como restricciones para poder imprimir los datos cumpliendo con el formato del input.pgm

        for(int j = 0; j<width; j++){
            fprintf(archivo, "%hhu ", *(pixels + a));   //cabe aclarar que pixels puede ser cualquier puntero, ya sea el umbralizado o el negative
            a++;
        }
        fprintf(archivo, "\n");

    }
    fclose(archivo);

}

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

/*
=================================================== SECCION DE MAIN =====================================================
*/

int main (void){ 
    int width, height, max_val, threshold, total_datos;
    char filename [100];        //aca se inicializan todas las variables, entre ellas la variable del nombre del archivo
    char umbralizado_filename [100];    //se ponen dos nuevas varibales de caracteres para tener mas orden en la escritura de archivos
    char negative_filename [100];
    unsigned char *pixels = NULL;       //se inicializa el puntero
    unsigned char *negative = NULL; 
    unsigned char *pixels_original = NULL; //se inicializa un putero a manera de copia del puntero original pues el umbral se aplicaba sobre el original

    
    
    printf("Ingrese el nombre del archivo (<archivo>.pgm) : ");
    scanf("%99s", filename);

    pixels = read_pgm(filename, &width, &height, &max_val); //aca se iguala directamente con la funcion pues se retorna un puntero directamente
    pixels_original = read_pgm(filename, &width, &height, &max_val);

    total_datos = width * height; //cabe aclarar que este dato debe ser tomado despues de la funcion read_pgm pues sino los valores no han sido asignados todavia


    printf("Ingrese el umbral: ");
    scanf("%d", &threshold);        //aca se lee el umbral ingresado por el usuario

    apply_threshold(pixels,total_datos,threshold); 
    negative = make_negative(pixels,total_datos);   //se iguala a negative pues retorna un puntero de un array de datos

    printf("Ingrese el nombre del archivo (<archivo>.pgm) a crear para el umbralizado : "); //para ambos archivos se solicita un nombre y luego se utiliza la misma funcion
    scanf("%99s", umbralizado_filename);                                                    //para generar un archivo con ambos punteros

    write_pgm(umbralizado_filename, pixels, width, height, max_val);


    printf("Ingrese el nombre del archivo (<archivo>.pgm) a crear para el negativo : ");
    scanf("%99s", negative_filename);

    write_pgm(negative_filename, negative, width, height, max_val);

    print_stats(pixels_original,pixels,total_datos);


    free(pixels_original);
    free(pixels);
    free(negative);
    

    return 0;
}