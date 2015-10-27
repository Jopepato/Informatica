/**
	\file Punto2D.hpp
	\brief Punto2D representa la clase punto del plano euclídeo definida mediante plantilla (template)
	\author Jose Pérez-Parras Toledano
	\date 1 de Marzo de 2015
*/

#ifndef PUNTO2D_H_
#define PUNTO2D_H_


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <fstream>

using namespace std;

/*!
	\brief Espacio de nombres para la asignatura de Estructura de datos.
*/
namespace ed{

//Cuando se utilizan templates se suele hacer todo en el mismo hpp

//!Definicion de la plantilla para la clase Punto2D
template <class T>
class Punto2D{

	//! \name Atributos privados de la clase Punto2D
	private:
		T x_; //!< abcisa del Punto
		T y_; //!< ordenada del Punto

	//! \name Atributos publicos de la clase Punto2D
	public:

		//! \name Constructores de la clase Punto2D

		/**
			\brief Constructor que crea un Punto2D a partir de sus coordenadas x e y
			\attention Función sobrecargada
			\note Los parámetros tienen valores por defecto
			\param x de tipo T, valor por defecto 0
			\param y de tipo T, valor por defecto 0
			\pre Ninguna
			\post Ninguna
			\sa setX(), setY()
		*/
		inline Punto2D(T x=0, T y=0){
								 x_ = x;
						     y_ = y;
								};

		/**
			\brief Constructos que crea un Punto2D a partir de otro Punto2D
			\attention Función sobrecargada
			\param p de tipo Punto2D pasado por referencia constante
			\pre El punto p debe existir
			\post Ninguna
			\sa setX(), setY(), getX(), getY()
		*/
		inline Punto2D(Punto2D const &p){
				setX(p.getX());
				setY(p.getY());
				};

		//! \name Getters de la clase Punto2D

		/**
		\brief Devuelve la coordenada "X" del punto
		\return Componente "x" del punto2D (Tipo T)
		\pre El punto debe existir
		\post Ninguna
		\sa getY()
		*/
		inline T getX()const{return x_;};

		/**
		\brief Devuelve la coordenada "Y" del punto
		\return Componente "y" del punto2D (Tipo T)
		\pre El punto debe existir
		\post Ninguna
		\sa getX()
		*/
		inline T getY()const{return y_;};

		//! \name Setters de la clase Punto2D

		/**
		\brief Asigna un valor "x" a la coordenada X del punto
		\param x de tipo T
		\pre El punto debe existir
		\pos Ninguna
		\sa setY()
		*/
		inline void setX(const T &x){x_ = x;};

		/**
		\brief Asigna un valor "y" a la coordenada y del punto
		\param y del tipo T
		\pre El punto debe existir
		\post Ninguna
		\sa setX()
		*/
		inline void setY(const T &y){y_ = y;};

		//! \name Funciones de la clase Punto2D

		/**
		\brief Comprueba si dos puntos son iguales
		\param p de tipo Punto2D
		\return booleano para saber si son iguales o no
		\pre Ambos puntos deben existir
		\post Ninguna
		\sa getX(), getY()
		*/
		 inline bool SonIguales(Punto2D p){
				if(this.getX() == p.getX() && (this.getY() == p.getY()) ){
					return true;
				}else{
					return false;
				}
		};

		/**
		\brief Sobrecarga del operador igual para asignar dos puntos
		\attention Se sobrecarga el operador de asignacion "="
		\param q una referencia constante del tipo Punto2D
		\pre Ambos puntos deben existir
		\post El punto a la izquierda del operador "=" debe ser igual al punto de la derecha
		\sa getX(), getY(), setX(), setY()
		*/
		inline Punto2D & operator=(Punto2D const &q){

			if(this != &q){
			setX(q.getX());
			setY(q.getY());
			}
			return *this;
		};

		/**
		\brief Pide al usuario que introduzca los datos del punto por teclado
		\pre El punto debe existir
		\post El punto debe tener los valores introducidos por el usuario
		\sa setX(), setY()
		*/
		inline void leerPunto2D(){

			T aux;
			cout << "Introduzca el punto X";
			cin >> aux;
			setX(aux);
			cout << "Introduza el punto Y";
			cin >> aux;
			setY(aux);
		};

		/**
		\brief Muestra por pantalla las coordenadas de un punto
		\pre El punto debe existir
		\post Se deben haber mostrado las coordenadas por pantalla
		\sa getX(), getY()
		*/
		inline void escribirPunto2D(){

			cout << "Punto X: " << getX() << endl;
			cout << "Punto Y: " << getY() << endl;
		};

};

} //\brief Fin de nampespace ed



#endif
