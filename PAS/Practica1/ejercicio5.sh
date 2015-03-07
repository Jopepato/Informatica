#!/bin/bash
if [ $# -eq 2 ]
	then
	
	for x in $(find "$1" -name "*$2*")
		do
				if [ -x $x ] #Con esto sabemos si es ejecutable
					then
						echo "$x"";"$(stat -c %s $x)";"$(stat -c %i $x)";"$(stat -c %A $x)";1;"
					else 
						echo "$x"";"$(stat -c %s $x)";"$(stat -c %i $x)";"$(stat -c %A $x)";0;"
				fi
		done
	else
		echo "Numero de parametros incorrectos"
fi
