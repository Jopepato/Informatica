#!/bin/bash
function recorre()
{
	echo "<ul>" >> $1.html

	for x in $(find $2 -maxdepth 1)
		do

		if [ $x != $2 ]
			then
				if [ -d $x ]
					then
						echo "<li><strong>$x</strong></li>" >> $1.html

						recorre $1 $x

						echo "</ul>">> $1.html
				else
					echo "<li>$x</li>" >> $1.html
				fi
		fi

		done

}



if [ ! $# -eq 1 ]
	then
		echo "Numero de parametros introducidos incorrecto"
	else
	#Comenzamos :>

		if [ -d $1 ]
			then

			#Hacemos cosas
				echo -e "<html>\n<title>Lista de la carpeta $1</title>\n<body>" >> $1.html
				echo "<h1>Ejercicio2_PAS</h1>" >> $1.html

				#Le pasamos dos porque el primer siempre será para hacer referencia al archivo
				recorre $1 $1

				#Ahora tenemos que cerrar el html
				echo "</body></html>" >> $1.html

			else
			echo "Carpeta introducida no valida"

		fi
fi