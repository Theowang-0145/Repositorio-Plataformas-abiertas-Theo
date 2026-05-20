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
        scanf("%f", &sensores[i].valor);        //se utiliza el valor i para ir variando de los valore de los sensores
       
        sensores[i].estado = clasificar (sensores[i].valor);     //se hace un llamado a la funcion de clasificar el valor ingresado   
        a++;                                                     //esta funcion retorna una variable de estado, la cual se le asigna un numero
    }                                                            //pues es un dato tipo enum, por lo que luego hay que darle un valor mas legible

    printf("\n Tabla de lecturas: \n");
    printf("|-ID-|-Valor-|-Estado-| \n");           //este es el inicio de la tabla

    for (i = 0; i < MAX_SENSORES; i++){             //se utiliza otra vez un ciclo for para imprimir los demas datos de manera seguida 
        printf("|-%d-|-%.2f-|-%s|\n",sensores[i].id,sensores[i].valor,
        (sensores[i].estado == NORMAL) ? "NORMAL" :         //con este condicional se imprimen los datos obtenidos por el valor
        (sensores[i].estado == ALERTA) ? "ALERTA" :         //resulta necesario para poder pasar el enum a algo imprimible.
        "FALLO");
    }


    return 0; 
}