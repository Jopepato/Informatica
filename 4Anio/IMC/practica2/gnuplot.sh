#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "CCRDigits.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "CCR Train"
plot 'ccr.txt' using 1:2 t "CCR Online" w l, 'ccr2.txt' using 1:2 t "CCR Offline" w l

_end_