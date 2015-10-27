#!/bin/bash

if [ $# -eq 2 ]
	then


	j=0
	num=0

	while read line
		do
			let "j++"
		done < $1

	#Ahora usamos el grep y el cut para coger los numeros de las lineas

	for x in $(grep $2 $1 -n | cut -d ":" -f1)
		do
			i=0
			
					#Ahora en x tendremos almacenado el valor de la linea

					echo "Encuentro numero $num"
					echo "---------------------"

			
			while read line
				do
			#Tenemos 3 opciones
					let "i++"
				#Primera: Si es la primera linea

					if [ $x -eq 1 ]
					then
						if [ $i -eq $x -o $((i-1)) -eq $x ]
							then
								echo "$line"
						fi
					fi

				#Si esta por la mitad

					if [ $x -gt 1 -a $x -lt $j ]
						then
							#Imprimimos esa, la siguiente y la de antes
							if [ $((i+1)) -eq $x -o $i -eq $x -o $((i-1)) -eq $x ]
								then
									echo "$line"
							fi
					fi

				#Si esta en la ultima linea
					if [ $x -eq $j ]
						then
							#Imprimimos solo la de antes
							if [ $((i+1)) -eq $x -o $i -o $x ]
								then
									echo "$line"
							fi
					fi

				done < $1

				let "num++"
				echo ""
		done

		echo "-----------------------------------"


	else 
	echo "jijijijijijii:>"
fi