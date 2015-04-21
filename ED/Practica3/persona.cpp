/*!
  \file persona.cpp
  \brief  Definicion de la clase Clave 
  \author Jose Perez-Parras Toledano
  \date   14/05/2015
*/
#include <iostream>
#include "persona.hpp"

edi::Persona::Persona(const  std::string &n, const  std::string &a, const int &d)
{
	nombre(n);
	apellido(a);
	dni(d);
  borrado('n');
};

edi::Persona::Persona()
{
	nombre("");
	apellido("");
	dni(0);
  	borrado('n');
};
		
edi::Persona::Persona(const edi::Persona &p)
{
	*this = p;
};

edi::Persona & edi::Persona::operator=(const edi::Persona &p)
{
	if (this != &p)
	{
		nombre(p.nombre());
		apellido(p.apellido());
		dni(p.dni());
	}
	return *this;
};
	
bool edi::Persona::operator==(const edi::Persona &p) const
{
	return apellido() == p.apellido() and nombre() == p.nombre() and dni() == p.dni();
};

//Sobrecarga del operador < para la ordenación.
bool edi::Persona::operator<(const edi::Persona &p) const
{
	if (apellido() < p.apellido())
		return true;
	else if (apellido() == p.apellido())
	{
		if (nombre() < p.nombre())
			return true;
		else if (nombre() == p.nombre())
		{
			if (dni() < p.dni())
				return true;
			return false;
		}
		else
			return false;
	}
	else
		return false;
};

bool edi::Persona::operator<=(const edi::Persona &p) const
{
	return (*this < p or *this == p);
};

bool edi::Persona::operator>(const edi::Persona &p) const
{
	return not (*this <= p);
};

bool edi::Persona::operator>=(const edi::Persona &p) const
{
	return not (*this < p);
};

// IMPORTANTE:: Las funciones amigas se incluyen en el espacio de nombres edi
/*! 
  \brief Espacio de nombres de la asignatura de Estructuras de datos y de la información
*/
namespace edi{
	/*! 
		\fn     std::ostream & operator<<( std::ostream &stream, const edi::Persona &p)
		\brief  Escribe los datos de la Persona en un flujo de salida
		\note   Sobrecarga del operador de salida "<<"
		\param	stream Flujo de salida
		\param  p Persona, cuyos datos se van a escribir en el flujo de salida
		\return Flujo de salida en el que se han escrito los datos de la Persona
		\sa     operator>>
	*/
	std::ostream & operator<<( std::ostream &stream, const edi::Persona &p)
	{
		stream << p.nombre() << " " << p.apellido() << " " << p.dni() <<  std::endl;
		return stream;
	};

	/*! 
		\fn     std::istream &operator>>( std::istream &stream, edi::Persona &p)
		\brief  Lee los datos de la Persona desde un flujo de entrada
		\note   Sobrecarga del operador de salida ">>"
		\param	stream Flujo de entrada
		\param  p Persona, cuyos datos se van a leer desde el flujo de entrada
		\return Flujo de salida en el que se han escrito los datos de la Persona
		\sa     operator<<
	*/
	std::istream &operator>>( std::istream &stream, edi::Persona &p)
	{
		char aux[30];
		int dni;
		std::cout << "Nombre: ";
		stream >> aux;
		p.nombre(aux);
		std::cout << "Apellido: ";
		stream >> aux;
		p.apellido(aux);
		std::cout << "Dni: ";
		stream >> dni;
		p.dni(dni);
		p.borrado('n');
		
		return stream;
	};

	std:ofstream & operator<<(std::ofstream& out, Persona const& p){
		//Lee del fichero




	};


	friend std::ifstream operator>> (std::ifstream& in, Persona& p){
		//Escribe en el fichero

	};
}

const  std::string & edi::Persona::nombre()const
{
	return _nombre;
};

const  std::string & edi::Persona::apellido()const
{
	return _apellido;
};

const int & edi::Persona::dni() const
{
	return _dni;
};

const char & edi::Persona::borrado() const
{
	return _borrado;
};

void edi::Persona::nombre(const  std::string &nombre)
{
	_nombre = nombre;
};

void edi::Persona::apellido(const  std::string &apellido)
{
	_apellido = apellido;
};

void edi::Persona::dni(const int &dni)
{
	_dni = dni;
};

void edi::Persona::borrado(const char &borrado)
{
	_borrado = borrado;
};

