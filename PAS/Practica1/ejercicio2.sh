#!/bin/bash
html="$1.html"
function recorrer_directorio()
{
 dir=$(dir -1)
 for file in $dir;
 do
# comprobamos que la cadena no este vacía
  if [ -n $file ]; then
    printf  "<ul><strong>$file</strong></ul>" > $html
   if [ -d "$file" ]; then

# si es un directorio, accedemos a él,
# llamamos recursivamente a la función recorrer_directorio
    # echo "DIR: " $file
    printf  "<li>$file</li>" > $html
    cd $file
    recorrer_directorio ./
# una vez que hemos terminado, salimos del directorio (IMPORTANTE)
    cd ..
      else
# dividimos la extensión del nombre del fichero y lo mostramos en pantalla
    extension=${file##*.}
    path_and_name=${file%.*}
    echo "Fichero: "$path_and_name"__".$extension
   fi;
  fi;
 done;
}

if [ ! $# -eq 1 ];
then
  echo "Debes introducir el directorio que quieres recorrer"
else
  echo "Generando html"
  printf  "<html>\n<head>\n\t<title>ejercicio2</title>\n</head><body>\n\t\t<h1>Lista del directorio $1 </h1>\n<br></br>" > $html
  dir=$1
  cd $dir
  recorrer_directorio $dir
  cd ..
  printf "\n</html>" > $html
  echo "Terminado!"
fi
