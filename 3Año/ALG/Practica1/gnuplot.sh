#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "practica1.eps"
set key right bottom
set xlabel "Numero de elementos"
set ylabel "Tiempos (microsegundos)"
plot 'Datos.txt' using 1:2 t "Tiempo Medio Burbuja" w l, 'Datos.txt' using 1:3 t "Tiempo Estimado Burbuja" w l, 'Datos.txt' using 1:4 t "Tiempo Medio Qsort Iteract." w l, 'Datos.txt' using 1:5 t "Tiempo Estimado Qsort Iteract." w l
_end_