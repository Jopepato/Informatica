/*!
  \file persona.cpp
  \brief  Implememación de la clase Persona 
  \author Name
  \date   16/03/2015
*/

#include <iostream>
#include <cstring>
#include "persona.hpp"

using namespace std;
using namespace edi;



//////////////////////////////////////////////////////////////
// IMPORTANTE

// Las funciones amigas se incluyen en el espacio de nombre edi
namespace edi{


ostream & operator<<(ostream &stream, const Persona &p)
{
	stream << p.nombre() << " " << p.apellido() << " " << p.dni() << endl;
	return stream;
};



istream &operator>>(istream &stream, Persona &p)
{
	char aux[30];
	int dni;

	cout << "Nombre: ";
	stream >> aux;
	p.nombre(aux);

	cout << "Apellido: ";
	stream >> aux;
	p.apellido(aux);

	cout << "Dni: ";
	stream >> dni;
	p.dni(dni);

	// 
	p.borrado('n');
	
	return stream;
};
} // fin del espacio de nombres edi

//////////////////////////////////////////////////////////////


Persona::Persona(const char * n, const char * a, const int &d)
{
	nombre(n);
	apellido(a);
	dni(d);
	borrado('n');
};

Persona::Persona()
{
	nombre("");
	apellido("");
	dni(0);
  	borrado('n');
};
		
Persona::Persona(const Persona &p)
{
	*this = p;
};

Persona & Persona::operator=(const Persona &p)
{
	if (this != &p)
	{
		nombre(p.nombre());
		apellido(p.apellido());
		dni(p.dni());
	}
	return *this;
};
	
bool Persona::operator==(const Persona &p) const
{
	return strcmp(apellido(), p.apellido()) == 0 and strcmp(nombre(), p.nombre()) == 0 and dni() == p.dni();
};

//Sobrecarga del operador < para la ordenación.
bool Persona::operator<(const Persona &p) const
{
	if (strcmp(apellido(), p.apellido()) < 0)
		return true;
	else if (strcmp(apellido(), p.apellido()) == 0)
	{
		if (strcmp(nombre(), p.nombre()) < 0)
			return true;
		else if (strcmp(nombre(), p.nombre()) == 0)
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

bool Persona::operator<=(const Persona &p) const
{
	return (*this < p or *this == p);
};

bool Persona::operator>(const Persona &p) const
{
	return not (*this <= p);
};

bool Persona::operator>=(const Persona &p) const
{
	return not (*this < p);
};



const char *Persona::nombre()const
{
	return (char *)_nombre;
};

const char * Persona::apellido()const
{
	return (char *)_apellido;
};

const int &Persona::dni() const
{
	return _dni;
};

const char &Persona::borrado() const
{
	return _borrado;
};

void Persona::nombre(const char * nombre)
{
	strcpy(_nombre, nombre);
};

void Persona::apellido(const char * apellido)
{
	strcpy(_apellido, apellido);
};

void Persona::dni(const int &dni)
{
	_dni = dni;
};

void Persona::borrado(const char &borrado)
{
	_borrado = borrado;
};
