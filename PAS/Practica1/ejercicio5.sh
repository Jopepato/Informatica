#!/bin/bash
if [ $# -eq 2 ]
	then

	for x in $(find "$1" -name "*$2*")
		do
				if [ -x $x ] #Con esto sabemos si es ejecutable
					then
						echo "$x;$(stat -c %s $x);$(stat -c %i $x);$(stat -c %A $x);1;"
					else
						echo "$x;$(stat -c %s $x);$(stat -c %i $x);$(stat -c %A $x);0;"
				fi
		done
	else
				if [ $# -eq 0 ]	#No ha introducido ninguno parametro se buscando todos los ficheros de la carpeta actual

					for x in $(find)
					do
						if [ -x $x ] #Con esto sabemos si es ejecutable
						then
							echo "$x;$(stat -c %s $x);$(stat -c %i $x);$(stat -c %A $x);1;"
						else
							echo "$x;$(stat -c %s $x);$(stat -c %i $x);$(stat -c %A $x);0;"
						fi
					done
				fi

		#Comprobacion de parametros

			if[ $# -eq 1 -o $# -ge 3 ]
				then
						echo "Numero de parametros introducidos incorrectos"
			fi
fi
