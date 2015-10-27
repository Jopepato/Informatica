#!/bin/bash

if [ $# -lt 1 -o $# -gt 2 ]
	then
		echo "Numero de parametros introducidos incorrectos"

	else
		#Comprobamos que existe la carpeta que nos han pasado como parametro
		if [ -d $1 ]
			then
			#Creamos una carpeta temporal
			temp="temp.tmp"
			mkdir $temp

			#Recorremos la carpeta que nos han pasado para pasar las cosas a la temporal
				for x in $(find $1)
				do
					#Comprobamos que es una subcarpeta
					if [ -d $x ]
						then
							mkdir "$temp/$x"
						else
							cp $x $temp/$x
					fi
				done

			#Y ahora creamos el tar

			cd $temp

			if [ $# -eq 2 ]
				then
					tar -czvf "../$2" "$1"
					echo "Archivo $2 creado correctamente"
				else
					tar -czvf "../$1.tar.gz" "$1"
					echo "Archivo $1.tar.gz creado correctamente"
			fi

			cd ..

			rm -Rf $temp


			else
				echo "La carpeta introducida no es valida"
			fi

fi