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

							#Mostramos las linea anterior y posterior
								if [ $((i-1)) -eq $x -o $i -eq $x -o $((i+1)) -eq $x ]
									then
										#Ahora tenemos que comprobar si la linea que queremos leer es la primera
										if [ $x -eq 1 ]
											then
												var=1
										fi
										#Y comprobamos si esta en la ultima linea
										if [ $x -eq $j ]
											then
											var=2
										fi

										#Y ahora mostramos por pantalla dependiendo del caso
										case $var in
											0) echo "$line" ;;
											1) echo "La linea a leer es la primera :<" ;;
											2) echo "La linea a leer es la ultima :<" ;;
											*) echo "Algo ha fallado" ;;
										esac
								fi

					done < $1
					let "num++"
				done
	else
	echo "Numero de parametros introducidos incorrecto"

fi
