/*!
  \file clave.hpp
  \brief  Implememtación de la clase clave
  \author Jose Perez-Parras Toledano
  \date   14/04/2015
*/

#ifndef CLAVE_H_
#define CLAVE_H_

#include <iostream>
#include <cstdlib>

using namespace std;


/*! 
  \name Espacio de nombres de la asignatura de Estructuras de datos y de la información
*/
namespace edi{
	//!  Definición de la plantilla de la clase Clave
	class Clave{

			private:
				int DNI_; //!< Dni del item
				int pos_; //!< Posicion del item


			public:
				//! \name CONSTRUCTORES
				
			/*! 
				\fn        Clave();
				\brief     Constructor por defecto de la clase Clave
				\attention Función sobrecargada	
			*/			
				Clave(){
					setDni(0);
					setPosicion(0);
				}
		
			/*! 
				\fn    		Clave(const int  &DNI, const   &pos);
				\brief     Constructor parametrizado de la clase Clave
				\attention Función sobrecargada
				\param     DNI DNI del item
				\param     pos Posicion del item
			*/
				Clave(const int &DNI, const int &pos){
					setDni(DNI);
					setPosicion(pos);
				};

			/*!
				\fn 	Clave(const Clave &p)
				\brief 	Constructor de una clave a partir de otra
				\attention Funcion sobrecargada
				\param p Otra clave de la cual se cogeran los campos
			*/
				
				Clave(const Clave &p){
					*this = p;
				};


				//! \name OPERADORES

			/*! 
				\fn     Clave & operator=(const Clave &p);
				\brief  Sobrecarga del operador de asignación
				\param  c Clave que se va a copiar en la Clave actual
				\post   Los valores de la Clave creada deben ser iguales a los de la Clave c
				\return Referencia a la Clave actual
				\sa     operator==, operator<, operator<=, operator>, operator>=
			*/
				Clave & operator=(const Clave &c);

			/*! 
				\fn     bool operator==(const Clave &c)const;
				\brief  Sobrecarga del operador relacional de igualdad
				\param  c Clave con la que va a comparar a la Clave actual
				\post   El valor devuelto debe ser true si la Clave actual es igual a la Clave p y false en caso contrario
				\return Valor lógico que indica si la Clave actual es igual que la Clave c
				\sa     operator==, operator<, operator<=, operator>, operator>=
			*/
				bool operator==(const Clave &c)const;

						/*! 
				\fn     bool operator<(const Clave &p) const;
				\brief  Sobrecarga del operador relacional "menor que"
				\param  p Clave con la que va a comparar a la Clave actual
				\post   El valor devuelto debe ser true si la Clave actual es alfabéticamente posterior a la Clave p y false en caso contrario
				\return Valor lógico que indica si la ClaveClave actual es alfabéticamente anterior a la Clave p
				\sa     operator==, operator<=, operator>, operator>=
			*/

				bool operator<(const Clave &c) const;
			/*! 
				\fn     bool operator>(const Clave &p) const;
				\brief  Sobrecarga del operador relacional "mayor que"
				\param  p Clave con la que va a comparar a la Clave actual
				\return Valor lógico que indica si la Clave actual es alfabéticamente posterior a la Clave p
				\post   El valor devuelto debe ser true si la Clave actual es alfabéticamente posterior a la Clave p y false en caso contrario
				\sa     operator==, operator<, operator<=, operator>=
			*/	
				bool operator>(const Clave &c) const;
			/*! 
				\fn     bool operator<=(const Clave &p) const;
				\brief  Sobrecarga del operador relacional "menor o igual que"
				\param  p Clave con la que va a comparar a la Clave actual
				\return Valor lógico que indica si la Clave actual es alfabéticamente anterior o igual que la Clave p
				\post   El valor devuelto debe ser true si la Clave actual es alfabéticamente posterior o igual que la Clave p y false en caso contrario
				\sa     operator==, operator<, operator>, operator>=
			*/
				bool operator<=(const Clave &c) const;
			/*! 
				\fn     bool operator>=(const Clave &p) const;
				\brief  Sobrecarga del operador relacional "mayor o igual que"
				\param  p Clave con la que va a comparar a la Clave actual
				\return Valor lógico que indica si la Clave actual es alfabéticamente posterior o igual que la Clave p
				\post   El valor devuelto debe ser true si la Clave actual es alfabéticamente posterior o igual que la Clave p y false en caso contrario
				\sa     operator==, operator<, operator<=, operator>
			*/
				bool operator>=(const Clave &c) const;
			/*! 
				\fn     friend ostream & operator<<(ostream &stream, const Clave &p);
				\brief  Escribe los datos de la Clave en un flujo de salida
				\note   Sobrecarga del operador de salida "<<"
				\param	stream Flujo de salida
				\param  p Clave, cuyos datos se van a escribir en el flujo de salida
				\return Flujo de salida en el que se han escrito los datos de la Clave
				\sa    friend  std::istream & operator>>( std::istream &stream, Clave &p);
			*/

				friend std::ostream & operator<<(std::ostream &out, Clave const& c);
			/*! 
				\fn     friend istream & operator>>(istream &stream, Clave &p);
				\brief  Lee los datos de la Clave desde un flujo de entrada
				\note   Sobrecarga del operador de salida ">>"
				\param	stream Flujo de entrada
				\param  p Clave, cuyos datos se van a leer desde el flujo de entrada
				\return Flujo de salida en el que se han escrito los datos de la Clave
				\sa     friend  std::ostream & operator<<( std::ostream &stream, const Clave &p);
			*/	
				friend std::istream & operator>>(std::istream &in, Clave & c);
			/*! 
				\fn     friend ofstream & operator<<(ostream &stream, const Clave &p);
				\brief  Escribe los datos de la Clave en un fichero
				\note   Sobrecarga del operador de salida "<<"
				\param	stream Fichero
				\param  p Clave, cuyos datos se van a escribir en el fichero
				\return Flujo de salida en el que se han escrito los datos de la Clave
				\sa    friend  std::istream & operator>>( std::istream &stream, Clave &p);
			*/

				friend std::ofstream & operator<<(std::ofstream& out, Clave const& c);
			/*! 
				\fn     friend ifstream & operator>>(istream &stream, Clave &p);
				\brief  Lee los datos de la Clave desde un fichero
				\note   Sobrecarga del operador de salida ">>"
				\param	stream Fichero
				\param  p Clave, cuyos datos se van a leer desde el flujo de entrada
				\return Flujo de salida en el que se han escrito los datos de la Clave
				\sa     friend  std::ostream & operator<<( std::ostream &stream, const Clave &p);
			*/	
				friend std::ifstream & operator>> (std::ifstream& in, Clave& c);

				
				//! \name OBSERVADORES

			/*! 
				\fn     const int& getDni() const
				\brief  Funcion que permite consultar el dni de la clave
				\return valor del atributo DNI_
			*/

				const int& getDni() const{
					return DNI_;
				};
			/*! 
				\fn     const int& getPosicion() const
				\brief  Funcion que permite consultar la posicion de la clave
				\return valor del atributo pos_
			*/

				const int& getPosicion() const{
					return pos_;
				};

				//! \name MODIFICADORES

			/*! 
				\fn     void setDni(const int &dni)
				\brief  Funcion que permite modificar el atributo DNI_
				\param dni Nuevo dni para el atributo DNI_
			*/
				void setDni(const int &dni){
					DNI_ = dni;
				};

			/*! 
				\fn     void setPosicion(const int &pos)
				\brief  Funcion que permite modificar el atributo pos_
				\param dni Nuevo dni para el atributo pos_
			*/
				void setPosicion(const int &pos){
					pos_ = pos;
				};



	};

















};
#endif