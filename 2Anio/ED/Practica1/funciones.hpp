/**
\file funciones.hpp
\brief Declaración de las funciones usadas para el error y cargar los ficheros
\author José Pérez-Parras Toledano
\date 1 de Marzo de 2015
*/
#ifndef FUNCIONES_H_
#define FUNCIONES_H_


//Incluimos las librerias
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "Recta2D.hpp"
#include "Punto2D.hpp"

//Declaramos los espacios de nombres
using namespace std;
using namespace ed;

//Declaramos las funciones
void cargarContorno(vector< Punto2D <double> > &contorno, const char *ficheroContorno);
void cargarAproximacionPoligonal (vector<int> &aproximacionPoligonal, const char *ficheroAproximacionPoligonal);
double calcularError(const vector< Punto2D <double> > &contorno, const vector<int> &aproximacionPoligonal);

#endif
