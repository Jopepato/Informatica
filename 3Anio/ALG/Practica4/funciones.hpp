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
bool encuentraSolucion(vector<int> monedas, vector<int> &solucion,const int &dinero);

#endif
