#ifndef ALGORITMOS_HPP_
#define ALGORITMOS_HPP_

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std;

void ordenacionBurbuja(vector <int> &v);
void ordenacionQuicksortNoRe(vector <int> &v);
void rellenaVector(vector <int> &v, const int nEle);
void muestraVector(vector<int> &v);
bool estaOrdenado(vector<int> &v);
#endif
