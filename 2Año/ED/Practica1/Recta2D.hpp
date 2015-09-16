/**
	\file Recta2D.hpp
	\brief Recta2D representa la clase Recta del plano mediante plantilla
	\author Jose Pérez-Parras Toledano
	\date 1 de Marzo de 2015
*/

#ifndef RECTA2D_H_
#define RECTA2D_H_

#include "Punto2D.hpp"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;

/*!
	\brief Espacio de nombres para la asignatura de Estructura de datos.
*/
namespace ed{

//!Definicion de la plantilla para la clase Punto2D
template <class T>

class Recta2D{

	//! \name Atributos privados de la clase Recta2D
	private:
		T a_; //!< Valor "a" de la recta explicita
		T b_; //!< Valor "b" de la recta explicita
		T c_; //!< Valor "c" de la recta explicita

	//! \name Atributos públicos de la clase Recta2D
	public:


		//! \name Constructores de la clase Recta2D
			/**
			\brief Constructor de la clase Recta2D a traves de los 3 valores de la recta
			\attention Funcion sobrecargada
			\param a Una referencia constante de tipo T
			\param b Una referencia constante de tipo T
			\param c Una referencia constante de tipo T
			\pre Ninguna
			\post Ninguna
			\sa setA(), setB(), setC()
			*/
			inline Recta2D(T const& a, T const& b, T const& c){
			a_ = a;
			b_ = b;
			c_ = c;
		};

			/**
			\brief Constructor de la clase Recta2D a traves de dos puntos
			\attention Funcion sobrecargada
			\param p Una referencia constante de tipo Punto2D<T>
			\param q Una referencia constante de tipo Punto2D<T>
			\pre Los dos puntos deben existir y deben ser distintos
			\post Ninguna
			\sa setA(), setB(), setC()
			*/
			inline Recta2D(Punto2D<T>  &p, Punto2D<T>  &q){

			//Precondicion
			//assert(p.sonIguales(q) == false);

			//Cuerpo
			a_ = q.getY() - p.getY(); //y2 - y1
			b_ = p.getX() - q.getX(); //x1 - x2
			c_ = p.getY() * ( q.getX() - p.getX() ) - p.getX() *(q.getY() - p.getY() );//y1*(x2-x1) - x1*(y2-y1)

		};


		//! \name Observadores de la clase Recta2D

			/**
			\brief Observador del valor "a" de la recta
			\pre La recta debe existir
			\post Ninguna
			\return Componente "a" de la recta (Tipo T)
			\sa getB(), getC()
			*/
			inline T getA()const{return a_;};

			/**
			\brief Observador del valor "b" de la recta
			\pre La recta debe existir
			\post Ninguna
			\return Componente "b" de la recta (Tipo T)
			\sa getA(), getC()
			*/
			inline T getB()const{return b_;};

			/**
			\brief Observador del valor "c" de la recta
			\pre La recta debe existir
			\post Ninguna
			\return Componente "c" de la recta (Tipo T)
			\sa getA(), getB()
			*/
			inline T getC()const{return c_;};


		//! \name Modificadores de la clase Recta2D

			/**
			\brief Asigna un valor "a" a la componente A de la recta
			\param a Una referencia constante del tipo T
			\pre La recta debe existir
			\post Ninguna
			\sa setB(), setC()
			*/
			inline void setA(T const &a){a_ = a;};

			/**
			\brief Asigna un valor "b" a la componente B de la recta
			\param b Una referencia constante del tipo T
			\pre La recta debe existir
			\post Ninguna
			\sa setA(), setC()
			*/
			inline void setB(T const &b){b_ = b;};

			/**
			\brief Asigna un valor "c" a la componente C de la recta
			\param c Una referencia constante del tipo T
			\pre La recta debe existir
			\post Ninguna
			\sa setA(), setB()
			*/
			inline void setC(T const &c){c_ = c;};

		//! \name Funciones de la clase Recta2D

			/**
			\brief Funcion que devuelve la distancia entre un punto y una recta
			\pre El punto debe existir
			\post Ninguna
			\param p Punto2D de tipo T
			\return Real que almacena la distancia entre el punto y la recta
			\sa getA(), getB(), getC()
			*/
			inline double Distancia(Punto2D<T> p){
			double distancia;
			distancia = abs((p.getX()* getA()) + (p.getY() * getB()) + getC());
			distancia = (distancia)/(sqrt(pow(getA(), 2) + pow(getB(), 2)));

			return distancia;
		};

};


} //! \brief Fin del espacio de nombres ed


#endif
