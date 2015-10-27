#!/bin/bash

#Tengo que hacerlo con el comando who y el comando date sumando y restando
echo "Lista de usuarios conectados junto con el numero de horas, minutos y segundos que llevan conectados"



while read line
do
	#Con esto leemos las lineas del who
	usuario=$(echo $line | sed -n -r -e "s/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/\1/p")
	tiempo=$(echo $line | sed -n -r -e "s/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/\4/p")
	fecha=$(echo $line | sed -n -r -e "s/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/\3/p")

	segundosusu=$(date -d "$fecha $tiempo" +%s)

	#Convertimos los segundos a horas y minutos
	horas=$[($(date +%s)-$segundosusu)/3600]
	minutos=$[($(date +%s)-$segundosusu)/60%60]

	echo "El usuario: $usuario lleva $horas horas conectado, $minutos minutos y $(date +%S) segundos">>temp.tmp
done < <(who)

cat temp.tmp | sort -k3
rm temp.tmp