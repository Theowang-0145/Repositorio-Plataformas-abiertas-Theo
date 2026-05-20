#include <stdio.h>
#include <math.h>

/*
=================================================== SECCION DE PARAMETROS ================================================
*/

#define MAX_SENSORES 10

typedef enum { NORMAL, ALERTA, FALLO } EstadoSensor; //tipo de varibale nueva, recordar que equivalen a numeros

typedef struct {        //otro tipo de variable nueva, sin embargo se busca un arreglo de varios sensores con este tipo de valores
    int id;
    float valor;
    EstadoSensor estado;
} Lectura;

/*
=================================================== SECCION DE FUNCIONES ================================================
*/

EstadoSensor clasificar(float valor){           //Esta funcion devuelve un estado, pues es uno de los nuevos tipos de datos creados
    EstadoSensor estado; 

    if (valor <= 60.0 && valor >= 40.0) {       //en primer lugar se inicializa la variable con el tipo de dato del Estadosensor
        estado = NORMAL;                        //luego se determina en que rango se encuentra y asi luego retorne el estado correspondiente
    } else if ((valor < 40.0 && valor >= 20.0) || (valor <= 80.0 && valor > 60.0)) { //se plantea las condiciones y operadores logicos
        estado = ALERTA;                            
    } else {
        estado = FALLO;
    }
    return estado;
}
int contar_estado(Lectura s[], int n, EstadoSensor e);
int lectura_extrema(Lectura s[], int n);
 
/*
=================================================== SECCION DE MAIN =====================================================
*/
int main (void) {
    int i, a; 
    Lectura sensores[MAX_SENSORES]; //lo que quiere decir esto es que existen 10 sensores con 3 valores de parte del struct cada uno

    a = 1;
    for (i = 0; i < MAX_SENSORES; i++){     //for utilizado para el ingreso de los datos 
        printf("Ingrese el ID del sensor %d: ", a); //se utiliza a pues se necesita el valor del sensor que comienza en 1
        scanf("%d", &sensores[i].id);

        printf("Ingrese el valor del sensor %d: ",a);
        scanf("%f", &sensores[i].valor);
       
        sensores[i].estado = clasificar (sensores[i].valor);        
        a++;
    }

    printf("\n Tabla de lecturas: \n");
    printf("|-ID-|-Valor-|-Estado-| \n");

    for (i = 0; i < MAX_SENSORES; i++){
        printf("|-%d-|-%.2f-|-%s|\n",sensores[i].id,sensores[i].valor,
        (sensores[i].estado == NORMAL) ? "NORMAL" :
        (sensores[i].estado == ALERTA) ? "ALERTA" :
        "FALLO");
    }


    return 0; 
}