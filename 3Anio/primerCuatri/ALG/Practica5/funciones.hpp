#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_


#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <limits>
#include <ctime>
#include "moneda.hpp"
#include "ClaseTiempo.hpp"

using namespace std;

bool estaOrdenadoDesc(vector<int> v);
void muestraSolucion(vector<int> monedas, vector<int> solucion);
bool encuentraCambioVoraz(vector<int> monedas, vector<int> &solucion,const int &dinero);
bool encuentraCambioDinamico(vector<int> monedas, int &dinero, int ** matrizSolucion);
int minimo(int a1, int a2);
void muestraMatriz(int ** matriz,vector<int>monedas, int fil, int col);
bool rellenaSolucionDinamica(int ** matriz, int fil, int col, vector<int> monedas, vector<int> &solucion);
void guardaTiempos(const vector<int> muestras, const vector<double> tiempoVoraz, const vector<double> tiempoDinamico, string nombreFichero);
#endif
