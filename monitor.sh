#!/bin/bash

#=================================================#
#===================(Funciones)===================#


manejo_monitor() {
    echo "Se ha interrumpido el script"             #esta es la funcion que atrapa el comando digitado por el usuario
    kill "$PID" 2>/dev/null             #aqui el error lo manda a dev null
}

funcion_captura_datos() {

    Arch_LOG=$1             #se guarda el parametro en otra variable local para hacerle cambios
    intervalo=$2

    Datos="monitor_$PID.dat"          #se genera una nueva variable que contenga los datos generados durante proceso

    tiempo=0

    while ps -p "$PID" >/dev/null 2>&1; do 
        TIMESTAMP=$(date "+%Y-%m-%d_%H:%M:%S")   #Esto solo imprime el formato solicitado por el laboratorio
        Datos_agrupados=$(ps -p "$PID" -o %cpu,%mem,rss --no-headers)  #Esto solo saca los valores solicitados

        read CPU MEM RSS <<< "$Datos_agrupados"     #este comando manda los tres valores obtenidos de los datos y los asigna
        #echo "$CPU" >> pruebas_lab2.txt            #a las varibales que necesitamos guardar (cabe aclarar que para mantener un registro
        #echo "$MEM" >> pruebas_lab2.txt            #se mandan las varibales a otro archivo de texto)
        #echo "$RSS" >> pruebas_lab2.txt

        echo "$TIMESTAMP $CPU $MEM $RSS" >> "$Arch_LOG"       #se guardan las variables en el archivo
        echo "$tiempo $CPU $RSS" >> "$Datos"                  #se guardan las variables a graficar en el otro archivo para poder graficarlo

        sleep $intervalo                            #aqui se espera el intervalo de tiempo indicado
        tiempo=$(($tiempo + $intervalo))            #el tiempo corresponde al tiempo esperado mas el anterior
    done

    echo "Proceso finalizado"

}

#=====================(Main)======================#
if [ $# -lt 1 ]; then 

    echo "No se digitaron correctamente los parametros"
    echo "Uso: ./monitor.sh <"comando"> <intervalo>"        #condicional utilizado para verificar entrada de los parametros
    exit 1

fi

#echo "entraron las dos variables" > pruebas_lab2.txt

comando="$1"                        #rdta es una forma de hacerlo, sabiendo si el string esta vacio sin embargo hay una forma mas facil
if [ -z "$2" ]; then                # intervalo=$(2:-2) otra forma de hacerlo
    intervalo=2
else 
    intervalo=$2
fi

bash -c "$comando" &                #este es el comando que se utiliza para correr el comando 
PID=$!
#echo "$PID" >> pruebas_lab2.txt

Arch_LOG="Archivo_$PID.log"                         #aqui se hace una variable tal que se puedan guardar cosas en el archivo facilmente
Datos="monitor_$PID.dat"                            #igualmente para los datos
echo "TIMESTAMP CPU% MEM% MEM_RSS_KB" >> "$Arch_LOG"        #este es el encabezado del archivo


trap manejo_monitor SIGINT              #llamado de las dos funciones: 1 para el manejo del proceso, 2 para la recoleccion de datos
funcion_captura_datos $Arch_LOG $intervalo

#====================(Grafica)====================#

Imagen="monitor_$PID.png"
gnuplot << EOF
set terminal png size 1000,600
set output "$Imagen"

set title "Monitoreo de: $comando (PID $PID)"
set xlabel "Tiempo (s)"
set ylabel "CPU (%)"
set y2label "RSS (KB)"
set y2tics
set grid

plot "$Datos" using 1:2 with lines title "CPU", \         
     "$Datos" using 1:3 axes x1y2 with lines title "RSS"
EOF
#una vez creada la grafica con los dos comportamientos se envia un mensaje final
echo "Gráfica generada: $Imagen"




    
