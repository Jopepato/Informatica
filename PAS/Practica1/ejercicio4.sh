#!/bin/bash
if [  $# -eq 2 ]
	then
		
		grep $2 $1 --color -n

	else
	echo "Numero de parametros introducidos incorrecto"

fi
