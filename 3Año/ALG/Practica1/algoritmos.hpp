#ifndef ALGORITMOS_HPP_
#define ALGORITMOS_HPP_

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <stack>
#include <cmath>
#include <fstream>
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
									  const vector<double> &y,
									  const double &a0,
									  const double &a1,
									  vector<double> &yEstimada,
									  double &r2);

void calcularTiemposEstimadosCuadraticos(const vector<double> &x,
										 const vector<double> &y,
										 const double &a0,
										 const double &a1,
										 const double &a2,
										 vector<double> &yEstimada,
										 double &r2);

void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE,
					const vector<double> &tS, const vector<double> &tSE, string fichero);

void calculaTiempoEnDias(const int &n, const double &a0Lineal, const double &a1Lineal,
						 const double &a0Pol, const double &a1Pol, const double &a2Pol);

double determinanteDe2(double ** matriz);
double determinanteDe3(double ** matriz);
#endif
