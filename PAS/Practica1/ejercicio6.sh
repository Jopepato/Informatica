#!/bin/bash

#Si no nos pasa ningun argumento, tomamos la carpeta actual y buscamos los archivos
function ordenar
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

  if read -t 5 -p "Nombre para la carpeta de ficheros de cabecera:  " carpetacabecera;
    then
    echo ""
  else
    echo ""
    carpetacabecera="$HOME/include"
  fi

  if read -t 5 -p "Nombre para la carpeta con el codigo fuente " carpetafuente;
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


  #Y ahora metemos los archivos correspondientes en cada carpeta

    if [ $# -eq 0 ]
      then

        for x in $(find -name "lib*")
        do
            if [ ! -d $x ]
            then
            #Con cp es fichero origen, directorio destinatario
            cp $x $carpetalib
          fi
        done

        for x in $(find -name "*.h")
        do
            if [ ! -d $x ]
            then
            cp $x $carpetacabecera
          fi
        done

        for x in $(find -name "*.c*")
        do
            if [ ! -d $x ]
            then
            cp $x $carpetafuente
          fi
        done

        for x in $(find)
        do
          if [ -x $x ]
            then
            cp $x $carpetaejectuables
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


}


  if [ $# -eq 0 ]         #Aqui se mete si no le hemos metido argumentos
    then

      ordenar

  else
      for x in $($#)
      do
          ordenar $x
      done

  fi
