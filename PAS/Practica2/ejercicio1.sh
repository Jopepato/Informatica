#!/bin/bash

#Mostrar las lineas que contienen la duracion de la pelicula
echo "**********"
echo "1) Lineas con la duracion de las peliculas: "
cat peliculas.txt | grep -E 'min.'

#Mostrar el pais de las peliculas, viene entre []
echo "**********"
echo "2 ) Lineas coincidentes con el pais de la pelicula: "
cat peliculas.txt | grep -E '\[.*\]'

#Mostrar solo el pais, sin la linea completa
echo "**********"
echo "3) Solo los paises de las peliculas: "
cat peliculas.txt | grep -E -o '\[.*\]' | sed -r -e 's/\[//' | sed -r -e 's/\]//'

#Contar cuantas peliculas son de 2014 y cuantas de 2015
echo "**********"
echo "4.1) Peliculas de 2014: "
cat peliculas.txt | grep -E -c '2014'
echo "4.2) Peliculas de 2015: "
cat peliculas.txt | grep -E -c '2015'

#Ahora mostramos todo el fichero pero sin lineas en blanco
echo "**********"
echo "5) Fichero sin lineas vacias: "
cat peliculas.txt | grep -E .

#Otra forma seria
#cat peliculas.txt | grep -E -i '[[:alnum:]]
#Asi nos aseguramos de que todas las lineas tienen una letra o un numero y no estan vacias

#Mostrar aquellas lineas que empiezan por la letra c, haya o no espacio antes de ellas
echo "**********"
echo "6) Lineas que empiezan por la letra c con o sin espacios antes: "
cat peliculas.txt | grep -E -i '^c|^ *c'

#Mostrar aquellas lineas que contengan 'd' 'l' o 't' + una vocal y la misma letra
echo "**********"
echo "7) Lineas que contienen 'd' 'l' o 't' mas una vocal y la misma letra: "
cat peliculas.txt | grep -E -i 'd[aeiou]d|l[aeiou]l|t[aeiou]t'

#Todas aquellas letras que tengan 8 vocales 'a' o más minusculas o mayusculas no necesariamente seguidas
echo "**********"
echo "8) Lineas que contienen 8 'a' o mas"
#Esto no va
#Revisar
cat peliculas.txt | grep -E -i 'a{8,}?'


#Las lineas que terminan por 3 puntos y no empiezan por espacio
echo "**********"
echo "9) Lineas que terminan con tres puntos y no empiezan por espacio: "
cat peliculas.txt | grep -E -i '^([[:alnum:]]).*(\.\.\.)$'

#Mostrar entre comillas las vocales con tildes con sed
echo "**********"
echo "10) Vocales con tilde entre comillas: "
cat peliculas.txt | sed -e -r 's/[áéíóúÁÉÍÓÚ]/"\1"/'
