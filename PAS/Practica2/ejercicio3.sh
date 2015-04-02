#!/bin/bash

#Tengo que hacerlo con el comando who y el comando date sumando y restando
echo "Lista de usuarios conectados junto con el numero de horas, minutos y segundos que llevan conectados"

#hora=$(who | sed -n -r 's/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/\4/p')

#echo $hora
who | sed -n -r -e "s/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)/El usuario \1 lleva $[$(date +%H)-$(date -d \4 +%H)] horas, no se cuantos minutos y $(date +%S) segundos/p" | sort