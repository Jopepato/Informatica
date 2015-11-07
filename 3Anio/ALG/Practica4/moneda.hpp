#ifndef CAMBIO_HPP_
#define CAMBIO_HPP_

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include "funciones.hpp"

using namespace std;


class moneda{

	private:
		vector<int> monedas;

	public:
		inline moneda(){
			monedas.clear();
		};
		void muestraMonedas();
		inline vector<int> getMonedas(){
			return monedas;
		};
		void leerFichero(const string &nombreFichero);
		void ordenaMonedas();

};


#endif
