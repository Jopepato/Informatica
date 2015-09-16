#!/bin/bash

#Esto es para que coja los 50 primeros caracteres y ponga "..." al final ademas de formatear el año y el pais de la pelicula
cat peliculas.txt | sed -e 's/^\(.\{50\}\).*/\1.../' | sed -e 's/(\(.*\))/\1,/' | sed -e 's/\[//' | sed -e 's/\]//'
