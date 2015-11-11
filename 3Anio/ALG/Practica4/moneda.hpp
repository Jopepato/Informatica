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
		vector<int> monedas_;

	public:
		//Constructor
		inline moneda(){
			monedas_.clear();
		};
		//Observador
		inline vector<int> getMonedas(){
			return monedas_;
		};
		//Modificador
		inline void setMonedas(const vector<int> &monedas){
			monedas_ = monedas;
		};

		//Funciones
		void muestraMonedas();
		void leerFichero(const string &nombreFichero);
		void ordenaMonedas();

};


#endif
