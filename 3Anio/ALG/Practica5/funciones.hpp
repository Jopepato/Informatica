#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_


#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

using namespace std;

bool estaOrdenadoDec(vector<int> v);
void muestraSolucion(vector<int> monedas, vector<int> solucion);
bool encuentraCambioVoraz(vector<int> monedas, vector<int> &solucion,const int &dinero);
bool encuentraCambioDinamico(vector<int> monedas, int &dinero, int ** matrizSolucion);
int minimo(int a1, int a2);

#endif
