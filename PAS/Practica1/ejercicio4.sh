#!/bin/bash
if [  $# -eq 2 ]
	then
		num=0
		for x in $(grep $2 $1 -n | cut -d ":" -f1 ) #Con eso cogemos los numeros de las lineas
		do
			#Ahora tenemos que imprimir dichas lineas y una mas y una menos
			echo "---------------------"
			echo "Muestra numero: $num"
			i=0
			j=0
			var=0
			#Para contar las lineas del fichero
			while read line
			do
				let "j++"
			done < $1
				while read line
					do
						let "i++"


								#Vemos si es la primera linea
								if [ $x -eq 1 ]
									then
										#Imprimimos esa y la siguiente
										if [ $i -eq $x -o $((i+1)) -eq $x ]
											then
												echo "$line"
										fi
								fi



							#Vemos si no es ni la primera linea ni la ultima
							if [ $x -gt 1 -a $x -lt $j ]
								then
								if [ $((i-1)) -eq $x -o $i -eq $x -o $((i+1)) -eq $x ]
									then
											echo "$line"
								fi
							fi

							#Vemos si es la ultima linea

							if [ $x -eq $j ]
								then
									if [ $((i-1)) -eq $x -o $i -eq $x ]
										then
											echo "$line"
									fi

							fi

					done < $1
					let "num++"
				done
	else
	echo "Numero de parametros introducidos incorrecto"

fi
