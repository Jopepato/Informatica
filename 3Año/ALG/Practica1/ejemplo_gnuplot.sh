#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafica.eps"
set key right bottom
set xlabel "Numero de elementos"
set ylabel "Tiempos (microsegundos)"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Burbuja" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Burbuja" w l, 'Datos.txt' using 1:4 t "Tiempo Medio Qsort Interact." w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Qsort Interact." w l
_end_