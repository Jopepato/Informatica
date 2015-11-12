#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_


#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <limits>
#include "matriz.hpp"
#include "moneda.hpp"

using namespace std;

bool estaOrdenadoDec(vector<int> v);
void muestraSolucion(vector<int> monedas, vector<int> solucion);
bool encuentraCambioVoraz(vector<int> monedas, vector<int> &solucion,const int &dinero);
bool encuentraCambioDinamico(vector<int> monedas, int &dinero, int ** matrizSolucion);
int minimo(int a1, int a2);
void muestraMatriz(int ** matriz,vector<int>monedas, int fil, int col);
bool rellenaSolucionDinamica(int ** matriz, int fil, int col, vector<int> monedas, vector<int> &solucion);
#endif
