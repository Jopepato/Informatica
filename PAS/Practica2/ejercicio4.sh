#!/bin/bash

if [ ! $# -eq 2 ]
	then
	echo "Numero de parametros introducidos incorrectos"
	
	else

	echo "Procesando..."
	while read line
	do
		#Nos quedamos solamente con los segundos
		segundos=$(ping $line -c1 -W $2 | grep -E -o 'time=.* ' | sed -r -e 's/time=//')

		if [ "$segundos" == "" ]
			#Volcamos los resultados a un fichero para despues mostrarlos
			then
			echo "Tras $2 segundos no respondio la IP $line">> temp.tmp
			else
			echo "Tras $segundos responde la IP $line">> temp.tmp
		fi
	done < $1

	cat temp.tmp | sort

	rm temp.tmp
fi 
