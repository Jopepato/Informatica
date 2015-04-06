/*!
  \file   persona.hpp
  \brief  Definición de la clase Persona 
  \author Name
  \date   16/03/2015
*/

#ifndef _PERSONA_HPP_
#define _PERSONA_HPP_

// Entrada y salida 
#include <iostream>

// 
using std::ostream;
using std::istream;

/*!
   \brief Espacio de nombres para la asignatura de Estructura de datos y de la información
*/
namespace edi {

//!  Definición de la plantilla de la clase Persona
class Persona
{
	private:
		char _nombre[30];    //!< nombre de la Persona
		char _apellido[30];  //!< apellidos de la Persona
		int _dni;            //!< dni de la Persona  
		char _borrado;       //!< si toma el valor 'n' entonces se considera que la Persona está borrada

	public:

		//! \name CONSTRUCTORES

		/*! 
			\fn        Persona();
			\brief     Constructor por defecto de la clase Persona
			\attention Función sobrecargada	
			\note      Inicialmente se considera que la persona está borrada
			\pre       Ninguna
			\post      Ninguna
			\sa        Persona(const char * n, const char * a, const int &d); Persona(const Persona &p);
		*/
		Persona();

		/*! 
			\fn        Persona(const char * n, const char * a, const int &d);
			\brief     Constructor parametrizado de la clase Persona
			\attention Función sobrecargada
			\param     n Nombre de la Persona
			\param     a Apellidos de la Persona
			\param     d DNI de la Persona
			\pre       Ninguna
			\post      Los valores de los atributos deben ser los valores de los parámetros
			\sa        Persona(); Persona(const Persona &p);
		*/
		Persona(const char * n, const char * a, const int &d);


		/*! 
			\fn 	    Persona(const Persona &p);
			\brief      Constructor de copia de la clase Persona
			\attention  Función sobrecargada	
			\param      p Persona de la que se van copiar los valores de los atributos.
			\pre        Ninguna
			\post       Los valores de la Persona creada deben ser iguales a los de la Persona p
			\sa         Persona(); Persona(const char * n, const char * a, const int &d); 
		*/
		Persona(const Persona &p);


		//! \name OBSERVADORES

		/*! 
			\fn     const char * nombre()const;
			\brief  Función que permite consultar el nombre de la Persona
			\return valor del atributo _nombre
			\pre    La Persona debe existir
			\post   Ninguna
			\sa     const char * apellido()const; const int &dni()const; const char &borrado() const; 
 		*/
		const char * nombre()const;


		/*! 
			\fn     const char * apellido()const;
			\brief  Función que permite consultar el apellido de la Persona
			\return valor del atributo _apellido
			\pre    La Persona debe existir
			\post   Ninguna
			\sa    const char * nombre()const; const int &dni()const; const char &borrado() const; 
 		*/
		const char * apellido()const;

		/*! 
			\fn     const int &dni()const;
			\brief  Función que permite consultar el DNI de la Persona
			\return valor del atributo _dni
			\pre    La Persona debe existir
			\post   Ninguna
			\sa    const char * nombre()const; const char * nombre()const; const char &borrado() const; 
 		*/
		const int &dni()const;


		/*! 
			\fn     const char &borrado() const;
			\brief  Función que permite consultar el valor del atributo borrado de la Persona
			\return valor del atributo _borrado
			\pre    La Persona debe existir
			\post   Ninguna
			\sa    const char * nombre()const; const char * apellido()const; const int &dni()const;
 		*/
		const char &borrado() const;


		//! \name MODIFICADORES
		/*! 
			\fn     void nombre(const char * nombre);
			\brief  Función que permite modificar el nombre de la Persona
			\param  nombre Nuevo valor del atributo _nombre
			\pre    La Persona debe existir
			\post   El valor del atributo _nombre debe ser igual al valor del parámetro nombre
			\sa    void apellido(const char * apellido); void dni(const int &dni); void borrado(const char &borrado); 
 		*/
		void nombre(const char * nombre);


		/*! 
			\fn     void apellido(const char * apellido);
			\brief  Función que permite modificar el apellido de la Persona
			\param  apellido Nuevo valor del atributo _apellido
			\pre    La Persona debe existir
			\post   El valor del atributo _apellido debe ser igual al valor del parámetro apellido
			\sa    void nombre(const char * nombre); void dni(const int &dni); void borrado(const char &borrado); 
 		*/
		void apellido(const char * apellido);

		/*! 
			\fn     void dni(const int &dni);
			\brief  Función que permite modificar el dni de la Persona
			\param  dni Nuevo valor del atributo _dni
			\pre    La Persona debe existir
			\post   El valor del atributo _dni debe ser igual al valor del parámetro dni
			\sa     void nombre(const char * nombre); void apellido(const char * apellido); void borrado(const char &borrado); 
 		*/
		void dni(const int &dni);

		/*! 
			\fn     void borrado(const char &borrado);
			\brief  Función que permite modificar el dni de la Persona
			\param  borrado Nuevo valor del atributo _borrado
			\pre    La Persona debe existir
			\post   El valor del atributo _borrado debe ser igual al valor del parámetro borrado
			\sa     void nombre(const char * nombre); void apellido(const char * apellido); void dni(const int &dni);
 		*/
		void borrado(const char &borrado);


	         //! \name OPERADORES

		/*! 
			\fn     Persona & operator=(const Persona &p);
			\brief  Sobrecarga del operador de asignación
			\param  p Persona que se va a copiar en la Persona actual
			\return Referencia a la Persona actual
			\pre    La Persona p debe existir
			\post   Los valores de la Persona creada deben ser iguales a los de la Persona p
			\sa     operator==, operator<, operator<=, operator>, operator>=
 		*/
		Persona & operator=(const Persona &p);


		/*! 
			\fn     Persona & operator==(const Persona &p);
			\brief  Sobrecarga del operador relacional de igualdad
			\param  p Persona con la que va a comparar a la Persona actual
			\return Valor lógico que indica si la Persona actual es igual que la Persona p
			\pre    La Persona p debe existir
			\post   El valor devuelto debe ser true si la Persona actual es igual a la Persona p y false en caso contrario
			\sa     operator==, operator<, operator<=, operator>, operator>=
 		*/
		bool operator==(const Persona &p)const;

		/*! 
			\fn     Persona & operator<(const Persona &p);
			\brief  Sobrecarga del operador relacional "menor que"
			\param  p Persona con la que va a comparar a la Persona actual
			\return Valor lógico que indica si la Persona actual es alfabéticamente anterior a la Persona p
			\pre    La Persona p debe existir
			\post   El valor devuelto debe ser true si la Persona actual es alfabéticamente anterior a la Persona p y false en caso contrario
			\sa     operator==, operator<=, operator>, operator>=
 		*/
		bool operator<(const Persona &p) const;

		/*! 
			\fn     Persona & operator>(const Persona &p);
			\brief  Sobrecarga del operador relacional "mayor que"
			\param  p Persona con la que va a comparar a la Persona actual
			\return Valor lógico que indica si la Persona actual es alfabéticamente posterior a la Persona p
			\pre    La Persona p debe existir
			\post   El valor devuelto debe ser true si la Persona actual es alfabéticamente posterior a la Persona p y false en caso contrario
			\sa     operator==, operator<, operator<=, operator>=
 		*/
		bool operator>(const Persona &p) const;

		/*! 
			\fn     Persona & operator<=(const Persona &p);
			\brief  Sobrecarga del operador relacional "menor o igual que"
			\param  p Persona con la que va a comparar a la Persona actual
			\return Valor lógico que indica si la Persona actual es alfabéticamente anterior o igual que la Persona p
			\pre    La Persona p debe existir
			\post   El valor devuelto debe ser true si la Persona actual es alfabéticamente posterior o igual que la Persona p y false en caso contrario
			\sa     operator==, operator<, operator>, operator>=
 		*/
		bool operator<=(const Persona &p) const;

		/*! 
			\fn     Persona & operator>=(const Persona &p);
			\brief  Sobrecarga del operador relacional "mayor o igual que"
			\param  p Persona con la que va a comparar a la Persona actual
			\return Valor lógico que indica si la Persona actual es alfabéticamente posterior o igual que la Persona p
			\pre    La Persona p debe existir
			\post   El valor devuelto debe ser true si la Persona actual es alfabéticamente posterior o igual que la Persona p y false en caso contrario
			\sa     operator==, operator<, operator<=, operator>
 		*/
		bool operator>=(const Persona &p) const;

	         //! \name FUNCIONES AMIGAS

		/*! 
			\fn     friend ostream & operator<<(ostream &stream, const Persona &p);
			\brief  Escribe los datos de la Persona en un flujo de salida
			\note   Sobrecarga del operador de salida "<<"
			\param	stream Flujo de salida
			\param  p Persona, cuyos datos se van a escribir en el flujo de salida
			\return Flujo de salida en el que se han escrito los datos de la Persona
			\pre    La Persona p debe existir
			\post   El flujo de salida debe contener los datos de Persona
			\sa     operator>>
 		*/
		friend ostream & operator<<(ostream &stream, const Persona &p);


		/*! 
			\fn     friend istream & operator>>(istream &stream, Persona &p);
			\brief  Lee los datos de la Persona desde un flujo de entrada
			\note   Sobrecarga del operador de salida ">>"
			\param	stream Flujo de entrada
			\param  p Persona, cuyos datos se van a leer desde el flujo de entrada
			\return Flujo de salida en el que se han escrito los datos de la Persona
			\pre    La Persona p debe existir
			\post   La Persona p debe tener los datos leídos desde el flujo de entrada
			\sa     operator>>
 		*/
		friend istream & operator>>(istream &stream, Persona &p);


}; // Fin de la clase Persona

} // Fin de namespace edi

#endif