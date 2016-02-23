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

using namespace std;

//Indica si se puede colocar en ese lugar
bool lugar(int k, int x[]);
//En el vector almaceno la solucion
void nReinas(int n, int &contador);

void escribirSolucion(int x[], int n);

#endif