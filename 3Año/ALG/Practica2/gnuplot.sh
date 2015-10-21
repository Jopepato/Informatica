#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "AmbosDeterminantes.eps"
set key right bottom
set xlabel "Nivel de la matriz"
set ylabel "Tiempos (microsegundos)"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Iterativo" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Iterativo" w l, 'Datos.txt' using 1:4 t "Tiempo Medio Recursivo" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Recursivo" w l
set output "Iterativo.eps"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Iterativo" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Iterativo" w l
set output "Recursivo.eps"
plot 'Datos.txt' using 1:4 t "Tiempo Medio Recursivo" w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Recursivo" w l
_end_