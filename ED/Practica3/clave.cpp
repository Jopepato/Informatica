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


//Falta sobrecargar los operadores << y >>
namespace edi{
	
	friend std::ostream & operator<<(std::ostream &out, Clave const& c){
		out << c.getDni() << " " << c.getPosicion() << " " << std::endl;
		return(out);
	}

	friend std::istream & operator>>(std::istream &in, Clave& c){
		int dni;
		int pos;

		cout << "Dni: ";
		in >> dni;
		c.setDni(dni);

		cout << "Posicion: "
		in >> pos;
		c.setPosicion(pos);

		return(in);

	}

	friend std:ofstream & operator<<(std::ofstream &out, Clave const& c){
		out << c.getDni() << " " << c.getPosicion() << " " << std::endl;

		return(out);

	}

	friend std::ifstream & operator>>(std::ifstream &in, Clave &c){

		char aux[30];

		in >> aux;
		c.setDni(atoi(aux));
		in >> aux;
		c.setPosicion(atoi(aux));

		return(in);


	}

}