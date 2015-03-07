#!/bin/bash
#Contamos los archivos de este directorio
var=0
for x in $(find *)
do
  if [ -f $x ]
	#Con esto solo contamos los ficheros
  then
    let "var++"
  fi
done
echo -e "El número de archivos en la carpeta actual es: $var \n"

	#Ahora mostramos los usuarios
echo "Los usuarios conectados en este momento son:"
	who | awk '{ print $1 }' | uniq -c
echo ""
	#Lo metemos en una condicion para que si no se cumple, ponga por defecto el caracter 'a'
var=0
if read -t 5 -p "¿Qué caracter quieres contar? " caracter;then
    for x in $(find -name "*$caracter*")
    do
      echo "$x"
      let "var++"
    done
    echo "El carácter $caracter aparece $var veces en nombres de ficheros o carpetas contenidos en la carpeta actual"
  else
    for x in $(find -name "*a*")
    do
        echo "$x"
        let "var++"
    done
    echo "El carácter 'a' aparece $var veces en nombres de ficheros o carpetas contenidos en la carpeta actual"
fi
