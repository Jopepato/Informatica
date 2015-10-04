#ifndef ALGORITMOS_HPP_
#define ALGORITMOS_HPP_

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <stack>
#include <cmath>
using namespace std;


void ordenacionBurbuja(vector <double> &v);
void quickSortIterative (vector<double> &arr, int l, int h);
int partition (vector<double> &arr, int l, int h);
void swap ( double* a, double* b );
void rellenaVector(vector <double> &v, const int nEle);
void muestraVector(vector <double> &v);
bool estaOrdenado(vector<double> &v);
void calcularAjusteLineal(const vector<double> &x,
						 const vector<double> &y,
						 double &a0, double &a1);

void calcularAjustePolinomico(const vector<double> &x,
							 const vector<double> &y,
							 double &a0, double &a1, double &a2);

void calcularTiemposEstimadosLineales(const vector<double> &x,
									  const double &a0,
									  const double &a1,
									  vector<double> &yEstimada,
									  double &r2);

void calcularTiemposEstimadosCuadraticos(const vector<double> &x,
										 const double &a0,
										 const double &a1,
										 vector<double> &yEstimada,
										 double &r2);

double determinanteDe2(double * matriz[]);
double determinanteDe3(double * matriz[]);
#endif
