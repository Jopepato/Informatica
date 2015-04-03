#!/bin/bash

if [ $# -eq 1 ]
	then

	while read line;
	do
		#Primero guardamos en variables los nombres que vamos a mostrar
		logname=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\1/')
		uid=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\3/')
		gid=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\4/')
		gecos=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\5/')
		home=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\6/')
		shell=$(echo $line | sed -r 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/\7/')


		echo "***********"
		echo "Logname: $logname"
		echo "UID: $uid"
		echo "GID: $gid"
		echo "Gecos: $gecos"
		echo "Home: $home"
		echo "Shell: $shell"
		#Ahora con el gid buscamos los nombres de grupo en el otro fichero
		#Vemos si esta vacio
		if [ "$gid" == "" ]
			then
				groupname=""
			else
				while read lineagrupo;
				do
					numgroup=$(echo $lineagrupo |sed -r -n 's/(.*):(.*):(.*):(.*)/\3/p')
					if [ $numgroup -eq $gid ]
						then
						groupname=$(echo $lineagrupo |sed -r -n 's/(.*):(.*):(.*):(.*)/\1/p')
						echo "Nombre grupo: $groupname"
					fi
				done < <(cat /etc/group)
		fi

		#Ahora vemos si es ejecutable o no mirando el who

		while read lineausu;
		do
			if [ "$lineausu" == "$logname" ]
				then
					ejecutable=1
				else
					ejecutable=0
			fi

		done < <(who |sed -r -n 's/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/\1/p')

		echo "Logeado = $ejecutable"

	done < <(cat /etc/passwd | grep -E $1)
	else
	echo "Numero de argumentos invalidos, debes introducir una cadena de texto"
fi