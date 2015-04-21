/*!
  \file clave.hpp
  \brief  Implememtación de la clase Persona 
  \author Jose Perez-Parras Toledano
  \date   14/04/2015
*/

#ifndef CLAVE_H_
#define CLAVE_H_

#include <iostream>
#include <cstdlib>

using namespace std;



namespace edi{

	class Clave{

			private:
				int DNI_;
				int pos_;


			public:
				
				//El constructor normal
				Clave(const int &DNI, const int &pos){
					setDni(DNI);
					setPosicion(pos);
				};

				//El constructor a partir de otra clave
				Clave(const Clave &p){
					*this = p;
				};



				//Sobrecarga de operadores

				Persona & operator=(const Clave &c);

				bool operator==(const Clave &c)const;

				bool operator<(const Clave &c) const;

				bool operator>(const Clave &c) const;

				bool operator<=(const Clave &c) const;

				bool operator>=(const Clave &c) const;




				//Sobrecarga del operador << y >>

				friend std:ofstream & operator<<(std::ofstream& out, Clave const& c);

				friend std::ifstream & operator>> (std::ifstream& in, Clave& c);


				//Observadores

				const int& getDni() const{
					return DNI_;
				};

				const int& getPosicion() const{
					return pos_;
				};


				//Modificadores


				void setDni(const int &dni){
					DNI_ = dni;
				};

				void setPosicion(const int &pos){
					pos_ = pos;
				};



	};

















};
#endif