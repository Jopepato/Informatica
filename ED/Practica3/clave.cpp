/*!
  \file clave.cpp
  \brief  Implememtación de la clase Clave 
  \author Jose Perez-Parras Toledano
  \date   14/04/2014
*/


#include "clave.hpp"



using namespace std;




	//La sobrecarga

edi::Clave & edi::Clave::operator=(const edi::Clave &c){
	if (this != &c)
	{
		setDni(c.getDni());
		setPosicion(c.getPosicion());
	}
	return *this;
}

bool edi::Clave::operator==(const edi::Clave &c)const{
	return (getDni() == c.getDni())
}

bool edi::Clave::operator<(const edi::Clave &c) const{
	if (getDni() < c.getDni())
		return true;
	else if (getDni() == c.getDni())
	{
		return false;
	}
	else
		return false;
}

bool edi::Clave::operator>(const edi::Clave &c) const{

		return not(*this < c);
}

bool edi::Clave::operator<=(const edi::Clave &c) const{
		
	return (*this < c or *this == c);
}

bool edi::Clave::operator>=(const edi::Clave &c) const{

	return not(*this <= c);
}
