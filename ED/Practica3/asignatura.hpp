/*!
  \file   asignatura.hpp
  \brief  Clase asignatura que contendra el listado de alumnos
  \author Jose Perez-Parras
  \date   4/05/2015
*/
#ifndef ASIGNATURA_H_
#define ASIGNATURA_H_


#include "edi_LinkedList.hpp"
#include "persona.hpp"
#include <vector>
#include <iostream>
#include <fstream>

/*!
   \brief Espacio de nombres para la asignatura de Estructura de datos y de la información
*/
namespace edi{

/** 
@class Asignatura
@brief Clase asignatura que contiene una lista con los alumnos de una asignatura.
*/
class Asignatura{

	private:
		LinkedList<Persona> alumnos_; //Lista con los alumnos de la asignatura
		int numAlum_;//Numero maximo de alumnos en la asignatura

	public:

		//! \name CONSTRUCTORES
		Asignatura(const int &numAlum){
			assert(numAlum <= 100);
			//Si esta condicion no se cumple, no se puede crear la asignatura
			numAlum_ = numAlum;
		}

		//! \name Observadores

		/*! 
			\fn     inline void VectorALista(const vector<Persona>& vector)
			\brief  Pasa un vector de alumnos a una lista doblemente enlazada y ordenada
			\param	const vector<Persona>
 		*/
		inline void VectorALista(const vector<Persona>& vector){

			//Recorremos el vector y lo vamos pasando a la lista
			int tam = vector.size();
			for(int i=0; i<tam; i++){
				alumnos_.inserta(vector[i]);
			}
		};
		/*! 
			\fn     inline void MostrarListaAscendente()
			\brief  Muestra la lista ordenada ascendentemente
 		*/
		inline void MostrarListaAscendente(){
			Persona p;
			for(int i=0; i<numAlum_; i++){
				p = alumnos_.item(i);

				cout << p;
			}

		};
		/*! 
			\fn     inline void MostrarListaDescendente()
			\brief  Muestra la lista ordenada descendentemente
 		*/
		inline void MostrarListaDescendente(){
			Persona p;
			for(int i=numAlum_-1; i>=0; i--){
				p = alumnos_.item(i);

				cout << p;
			}

		};

		/*! 
			\fn     inline void ListadoEntreDosAlumnosAscendente(const Persona &alumno1, const Persona alumno2)
			\brief  Muestra los alumnos ordenados ascendentemente entre dos alumnos proporcionados
			\param	const Persona alumno1
			\param 	const Persona alumno2
 		*/
		inline void ListadoEntreDosAlumnosAscendente(const Persona &alumno1, const Persona alumno2){
			//Condiciones iniciales
			assert(alumnos_.findItem(alumno1) != -1);
			assert(alumnos_.findItem(alumno2) != -1);

			int pos1;
			int pos2;
			Persona p;
			pos1=alumnos_.findItem(alumno1);
			pos2=alumnos_.findItem(alumno2);

			if(pos1 == pos2){
				cout << alumno1;
			}else{
				if(pos1 > pos2){
					for(int i=pos2; i<=pos1; i++){
						p = alumnos_.item(i);
						cout << p;
					}
				}else{
						for(int i=pos1; i<=pos2; i++){
						p = alumnos_.item(i);
						cout << p;
					}
				}
			}



		};
		/*! 
			\fn     inline void ListadoEntreDosAlumnosDescendente(const Persona &alumno1, const Persona alumno2)
			\brief  Muestra los alumnos ordenados descendentemente entre dos alumnos proporcionados
			\param	const Persona alumno1
			\param 	const Persona alumno2
 		*/
		inline void ListadoEntreDosAlumnosDescendente(const Persona &alumno1, const Persona alumno2){
			//Condiciones iniciales
			assert(alumnos_.findItem(alumno1) != -1);
			assert(alumnos_.findItem(alumno2) != -1);

			//Lo mismo pero cambiamos los valores
			int pos1;
			int pos2;
			Persona p;

			pos1=alumnos_.findItem(alumno1);
			pos2=alumnos_.findItem(alumno2);

			if(pos1 == pos2){
				cout << alumno1;
			}else{
				if(pos1 > pos2){
					for(int i=pos1; i>=pos2; i--){
						p = alumnos_.item(i);
						cout << p;
					}
				}else{
						for(int i=pos2; i>=pos1; i--){
						p = alumnos_.item(i);
						cout << p;
					}
				}
			}

		};


		//! \name Modificadores

		/*! 
			\fn     inline void ModificarAlumno(const Persona &nueva, const Persona &vieja)
			\brief  Cambia los datos de un alumno por otros proporcionados por el usuario
			\param	const Persona nueva
			\param 	const Persona vieja
 		*/
		inline void ModificarAlumno(const Persona &nueva, const Persona &vieja){

			//Los datos introducidos deben pertenecer a alguien
			int pos=alumnos_.findItem(vieja);
			assert(pos!= -1);
			alumnos_.deletePosition(pos);
			alumnos_.inserta(nueva);

		}


};//Fin de la clase Asignatura

}//Fin del namespace edi
#endif