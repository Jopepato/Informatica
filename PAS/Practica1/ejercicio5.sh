#!/bin/bash
if [ $# -eq 2 ]
	then
	
	find "$1" -name "*$2*"


	else
		echo "Numero de parametros incorrectos"
fi
