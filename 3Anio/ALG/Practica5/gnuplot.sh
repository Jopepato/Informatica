#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "AmbosDeterminantes.eps"
set key right bottom
set xlabel "Cambio (centimos)"
set ylabel "Tiempos (microsegundos)"
plot 'tiempos.txt' using 1:2 t "Tiempo Medio Voraz" w l, 'tiempos.txt' using 1:3 t "Tiempo Medio Dinamico" w l
set output "Voraz.eps"
plot 'tiempos.txt' using 1:2 t "Tiempo Medio Voraz" w l
set output "Dinamico.eps"
plot 'tiempos.txt' using 1:3 t "Tiempo Medio Dinamico" w l
_end_