#!/bin/bash

#Si no nos pasa ningun argumento, tomamos la carpeta actual y buscamos los archivos
function creacionCarpetas
{
  if read -t 5 -p "Nombre para la carpeta de las librerias: " carpetalib;
    then
    echo ""
  else
    carpetalib="$HOME/lib"
    echo ""
  fi

  if read -t 5 -p "Nombre para la carpeta de ejecutables: " carpetaejectuables;
    then
    echo ""
  else
    carpetaejectuables="$HOME/bin"
    echo ""
  fi

  if read -t 5 -p "Nombre para la carpeta de ficheros de cabecera: " carpetacabecera;
    then
    echo ""
  else
    echo ""
    carpetacabecera="$HOME/include"
  fi

  if read -t 5 -p "Nombre para la carpeta con el codigo fuente: " carpetafuente;
    then
    echo ""
    else
      echo ""
      carpetafuente="$HOME/src"
  fi


  #Ya tenemos los nombres de las carpetas
  #Ahora las creamos en el directorio actual

  mkdir "$carpetalib"
  mkdir "$carpetaejectuables"
  mkdir "$carpetacabecera"
  mkdir "$carpetafuente"
}

function ordenarYCompilar
{

  #Y ahora metemos los archivos correspondientes en cada carpeta

    if [ $# -eq 0 ]
      then

        for x in $(find -name "lib*")
        do
            if [ ! -d $x ]
            then
            #Con cp es fichero origen, directorio destinatario
            cp -i $x $carpetalib
          fi
        done

        for x in $(find -name "*.h")
        do
            if [ ! -d $x ]
            then
            cp -i $x $carpetacabecera
          fi
        done

        for x in $(find -name "*.c*")
        do
            if [ ! -d $x ]
            then
            cp -i $x $carpetafuente
          fi
        done

        for x in $(find)
        do
          if [ -x $x ]
            then
            if [ ! -d $x ]
              then
            cp -i $x $carpetaejectuables
          fi
          fi
        done

    else

      #Ahora tenemos que buscar en la carpeta que nos ha pasado el usuario
      for x in $(find "$1" -name "lib*")
      do
          cp "$x" "$carpetalib"
      done

      for x in $(find "$1" -name "*.h")
      do
          cp "$x" "$carpetacabecera"
      done

      for x in $(find "$1" -name "*.c*")
      do
          cp "$x" "$carpetafuente"
      done

      for x in $(find "$1")
      do
        if [ -x $x ]
          then
          cp "$carpetaejecutables"
        fi
      done

    fi

    #Ahora compilamos los .c y los .cc
    if [ $# -eq 0 ]
      then
    echo "Compilando..."

    #Pasamos al log
    #sh > ejercicio6.log 2>>ejercicio6.log
    for x in $(find -name "*.c")
    do
      var1="$x"
      var2=$($var1 | cut -d "." -f1)
      #gcc $x -o $var1

    done

    for x in $(find -name "*.cpp")
    do
      var1="$x"
      var2=$($var1 | cut -d "." -f1)
      #g++ $x -o $var1
    done

  else

      cd $1

      for x in $(find -name "*.c")
      do

        gcc $x -o $x

      done

      for x in $(find $carpetaejecutables -name "*.cpp")
      do

        g++ $x -o $x
      done

      cd ..

fi
}

  #Empieza el principal




  if [ $# -eq 0 ]         #Aqui se mete si no le hemos metido argumentos
    then
      creacionCarpetas
      ordenarYCompilar

      echo "Terminado"

  else
    creacionCarpetas
      for x in $*
      do
          if [ -d $x ]
            then
          ordenarYCompilar $x
        else
          echo "El nombre $x no es un directorio"
        fi
      done
      echo "Terminado"

  fi
