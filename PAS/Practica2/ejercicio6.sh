#!/bin/bash

if [ $# -eq 1 ]
	then

	while read line
	do

		echo $line



	done < /etc/passwd

	else
	echo "Numero de argumentos invalidos, debes introducir una cadena de texto"
fi