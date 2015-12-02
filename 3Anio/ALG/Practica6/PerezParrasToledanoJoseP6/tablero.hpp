#ifndef TABLERO_HPP_
#define TABLERO_HPP_


#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include "funciones.hpp"


//Clase tablero que leera el fichero para almacenar las soluciones y mostrarlas por pantalla
class tablero{

		private:
			std::vector<vector <int> > tablero_;
			int reinas_;
			int soluciones_;

		public:
			inline tablero(int reinas, int soluciones){
				tablero_.clear();
				reinas_ = reinas;
				soluciones_ = soluciones;

			};

			void leeFichero(const string &nombreFichero);

			inline int getReinas(){
				return reinas_;
			};

			inline int getSoluciones(){
				return soluciones_;
			};

			inline void setReinas(int reinas){
				reinas_ = reinas;
			};

			inline void setSoluciones(int soluciones){
				soluciones_ = soluciones;
			};

			void muestraTableros();
			void muestraVectores();

};


#endif