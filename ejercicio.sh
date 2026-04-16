#!/bin/bash
#================================= Funciones (verificacion de parametros) ===================================#

verificacion_archivo() {

    #aca se recibe el parametro de la funcion 
    local archivo=$1

    if [ -e "$archivo" ];then 

        #se registra que si existe el archivo
        echo "Si existe el archivo" >> pruebas.txt

    else

        echo "ERROR: El archivo $archivo no existe, por favor reescribala correctamente"
        exit 1 

    fi
}

gestion_grupo() {

    #se recibe el parametro de la funcion
    local grupo=$1

    #se realiza la operacion siguiente para buscar dentro de todos los grupos el que se recibio como argumento 
    #seguidamente se guarda si lo encontro o dio error en una variable
    #getent busca exactamente lo que se pide en bases de datos del sistema
    getent group "$grupo" >> pruebas.txt
    validacion=$?

    #se compara con cero pues $? da tres valores: 0 si el anterio comando se ejecuto y salio bien, 1 si no encontro nada, 2 si da error
    if [ $validacion -eq 0 ]; then  

        echo "Grupo $grupo ya existe"

    else
        
        #comando para anadir grupo
        sudo addgroup $grupo 
        echo "Grupo $grupo creado"

    fi
}

gestion_usuario() {

    #se recibe el parametro 
    local usuario=$1
    local grupo=$2

    #funcion para buscar el usuario dentro de la base de datos
    getent passwd "$usuario" >> pruebas.txt
    validacion=$?

    if [ $validacion -eq 0 ]; then 

        #comando para anadir el usuario al grupo creado anteriormente
        sudo usermod -a -G $grupo $usuario
        echo "Usuario $usuario ya existe; agregado al grupo $grupo"

    else

        sudo adduser $usuario
        sudo usermod -a -G $grupo $usuario
        echo "Usuario $usuario creado; agregado al grupo $grupo"
        
    fi
}

permisos_usuario_grupo() {

    #se reciben los parametros en la funcion
    local usuario=$1
    local grupo=$2
    local archivo=$3

    #se hacen los comando para otorgarle permisos al usuario nuevo
    sudo chown $usuario:$grupo $archivo
    sudo chmod 740 $archivo

    #se manda una comprobacion del archivo creado y sus permisos a este otro texto 
    ls -l $archivo >> pruebas.txt

    echo "Archivo $archivo asignado a $usuario:$grupo con permisos 740"
}


#=========================================== Main ================================================#
#================================= Parte 1 (Verificacion root) ===================================#


#se guarda la salida del comando en una variable para compararla con root
user="$(whoami)"    

if [ "$user" != "root" ]; then 
    echo "ERROR: Debe ejecutar el script como root"
    exit 1 
else 
    #aqui se guarda en un documento por aparte si paso efectivamente la condicion
    echo "ejecutado como sudo" > pruebas.txt  
fi 

#================================= Parte 2 (Verificacion parametros) ===================================#

#aqui se reciben los argumentos y se meten en las varibales correspondientes
usuario=$1
grupo=$2
archivo_ruta=$3

if [ $# -ne 3 ]; then 

    echo "No se digitaron correctamente los parametros"
    echo "Uso: ./ejercicio.sh <usurario> <grupo> <archivo>"
    exit 1

elif  [ $# -eq 3 ]; then 

    #nuevamente se registra que si se recibieron correctamente los argumentos
    echo "Entraron las tres variables correctamente: $usuario $grupo $archivo_ruta" >> pruebas.txt

    #aca se realizan las diversas verificaciones de los argumentos y los procesos correspondientes
    verificacion_archivo $archivo_ruta
    gestion_grupo $grupo 
    gestion_usuario $usuario $grupo
    permisos_usuario_grupo $usuario $grupo $archivo_ruta
     
fi
