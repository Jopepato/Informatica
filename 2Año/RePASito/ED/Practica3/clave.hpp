#ifndef CLAVE_HPP_
#define CLAVE_HPP_


#include <iostream>
#include <cstdlib>
#include "persona.hpp"

using namespace std;

/*!
	\name espacio de nombres para la asignatura de edi
*/
namespace edi{

	class Clave{

			private:
				int dni_; //! < Dni de la clave
				int pos_; //! < posicion en la lista

			public:

				//! \name Constructores
				Clave(const int &dni,const int &pos);

				Clave(const Clave &c);

				//! \name Observadores

				const int &dni() const;

				const int &posicion() const;

				//! \name Modificadores

				void dni(const int &dni);

				void posicion(const int &dni);


				//! \name Operadores


				Clave & operator=(const Clave &c);

				bool operator==(const Clave &c) const;

				bool operator<(const Clave &c) const;

				bool operator>(const Clave &c) const;

				bool operator<=(const Clave &c) const;

				bool operator>=(const Clave &c) const;

				friend ostream & operator << (ostream &stream, const Clave &c);

				friend istream & operator >> (istream &stream, const Clave &c);

				friend ofstream & operator << (ofstream &stream, const Clave &c);

				friend ifstream & operator >> (ifstream &stream, const Clave &c);


	};








}











#endif