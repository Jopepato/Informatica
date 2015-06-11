#include "clave.hpp"


using namespace edi;


Clave::Clave(const int &dni, const int &pos){
	dni_ = dni;
	pos_ = pos;
}

Clave::Clave(const Clave &c){
	dni_ = c.dni();
	pos_ = c.posicion();
}


//Observadores
const int & Clave::dni()const{
	return dni_;
}

const int & Clave::posicion()const{
	return pos_;
}


//Modificadores

void Clave::dni(const int &dni){
	dni_ = dni;
}

void Clave::posicion(const int &pos){
	pos_ = pos;
}

//Operadores

 		//Los friend van dentro del namespace edi :>

Clave & Clave::operator=(const Clave &c){

		this->dni(c.dni());
		this->posicion(c.posicion());
		return(*this);

}

bool Clave::operator==(const Clave &c)const{
	return(this->dni()==c.dni());
}

bool Clave::operator<(const Clave &c)const{
	return(this->dni()<c.dni());
}

bool Clave::operator>(const Clave &c)const{
	return(this->dni()>c.dni());
}

bool Clave::operator<=(const Clave &c)const{
	return(this->dni()<=c.dni());
}

bool Clave::operator>=(const Clave &c)const{
	return(this->dni()>=c.dni());
}

namespace edi{

	ostream & operator << (ostream &stream, const Clave &c){
		cout << c.dni() << " " << c.posicion() << endl;
		return stream;
	}

	istream & operator >> (istream &stream, Clave &c){
		int dni, pos;

		cout << "Dni: ";
		stream >> dni;
		cout << "Posicion: ";
		stream >> pos;
		c.dni(dni);
		c.posicion(pos);

		return stream;
	}

	ofstream & operator << (ofstream &stream, const Clave &c){

		stream << c.dni() << "," << c.posicion() << endl;
		return stream;

	}

	ifstream & operator >> (ifstream &stream, Clave &c){

		int dni, pos;

		stream >> dni >> pos;

		c.dni(dni);
		c.posicion(pos);

		return stream;

	}

}