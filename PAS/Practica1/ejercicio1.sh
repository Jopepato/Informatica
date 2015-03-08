#!/bin/bash
function busqueda()
{
		for x in $(find $1)
		do
			if [ -d $x ] #Comprobamos si es una subcarpeta
			then
					mkdir "$2/$x"
			else
					var=$[$(date +%s)-$(stat $x -c %Y)]
					if [ $var -gt 20 ]
					then
						cp $x "$2/$x"
					fi
			fi
		done
}

#Comienzo del programa
if [ $# -lt 1 ] || [ $# -gt 2 ]
	then
	echo "Numero de parametros introducidos incorrectos"

	else
		if [ -d $1 ] #Comprobamos que la carpeta proporcionada existe
		then
		#Creamos una carpeta temporal para almacenar los ficheros
		temp="temporal.tmp"
		mkdir "$temp"

		#Ahora recorremos las carpetas buscando los ficheros que almacenaremos en la temporal
		
		busqueda $1 $temp

		#Y ahora comprimimos

		if [ $# -eq 1 ] #No nos ha ntroducido el nombre del tar
			then
				cd "$temp"
				tar -czvf "../$1.tar.gz" "$1"
				cd ..
			else
				cd "$temp"
				tar -czvf "../$2" "$1"
				cd ..
		fi
			rm -R "$temp"
		else
			echo "Carpeta no valida"
	fi

fi



