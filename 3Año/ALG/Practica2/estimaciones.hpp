#ifndef ESTIMACIONES_HPP_
#define ESTIMACIONES_HPP_

#include "funciones.hpp"


void calcularAjusteIterativo(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3);

void calcularAjusteRecursivo(const vector<double> &x, const vector<double> &y, double &a0, double &a1);

void calcularTiemposEstimadosIterativo(const vector<double> &x, const vector<double> &y, vector<double> yEst, double &a0, double &a1, double &a2, double &a3, double &r2);

void calcularTiemposEstimadosRecursivo(const vector<double> &x, const vector<double> &y, vector<double> yEst, double &a0, double &b);

void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE,
          const vector<double> &tS, const vector<double> &tSE, string fichero);

#endif