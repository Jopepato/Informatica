#ifndef ESTIMACIONES_HPP_
#define ESTIMACIONES_HPP_

#include "funciones.hpp"


double calcularAjusteIterativo(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3);

double calcularAjusteRecursivo(const vector<double> &x, const vector<double> &y, double &a0, double &b);

double calcularTiemposEstimadosIterativo(const vector<double> &x, const vector<double> &y, vector<double> yEst, double &a0, double &a1, double &a2, double &a3, double &r2);

double calcularTiemposEstimadosRecursivo(const vector<double> &x, const vector<double> &y, vector<double> yEst, double &a0, double &b);

void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE,
          const vector<double> &tS, const vector<double> &tSE, string fichero);

#endif