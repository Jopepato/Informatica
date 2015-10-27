#!/bin/bash

var=0

#Comprobamos el numero de archivos que hay en el directorio actual
#Lo podriamos hacer con wc pero no se como coger los que no son carpetas
#Asi que lo hago con un for chustero :>

for x in $(find)
	do
		if [ -f $x ]
			then
			let "var++"
		fi

	done

	echo "El numero de archivos en este directorio es $var"
	echo "------------------------------------------------"

#Mostrar los usuarios logeados

#Usaremos tuberias wapas wapas

who | awk '{ print $1 }'

echo "-----------------------------------------------------"


#Primero tenemos que preguntar al usuario

var=0

	if read -t 5 -p "¿Qué caracter quieres contar? " caracter
		then
			for x in $(find -name "*$caracter*")
				do
					let "var++"
				done
		else
			caracter=a
			echo ""
			for x in $(find -name "*$caracter*")
				do
					let "var++"
				done
	fi

	echo "El caracter $caracter aparece $var veces :>"
	echo "--------------------------------------"

