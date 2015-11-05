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


class cambio{

	private:
		vector<int> monedas;
		vector<int> solucion;
		int dinero;

	public:
		inline cambio(){
			monedas.clear();
			solucion.clear();
			dinero = 0;
		};
		void getMonedas();
		void getSolucion();
		inline int getDinero(){
			return dinero;
		};
		inline void setDinero(const int &din){
			dinero = din;
		};
		void leerFichero(const string &nombreFichero);
		bool encuentraSolucion();
		void ordenaMonedas();

};


#endif
