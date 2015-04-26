/*!
  \file   listaFichero.hpp
  \brief  Funciones para guardar y cargar listas de un fichero
  \author Jose Perez-Parras
  \date   26/04/2015
*/
#ifndef listaFichero_H_
#define listaFichero_H_

#include "persona.hpp"
#include "edi_LinkedList.hpp"
#include <fstream>


		/*! 
		\fn     inline void guardarListaFichero(const LinkedList<Persona>& lista, const char * fichero)
		\brief  Guarda una lista pasada por parametro en un fichero
		\param	const LinkedList<Persona>& lista
		\param 	const char * fichero
		*/

		inline void guardarListaFichero(const LinkedList<Persona>& lista, const char * fichero){

			//Recorrer la lista y guardar cada alumno en el fichero
			Persona p;
			fstream f;

			f.fopen(fichero);

			//Recorremos la lista entera y la guardamos en el fichero
			for(int i=0; lista.isValid(i); i++){	
				if(lista.isValid(i)){
					p = personas.item(i);

					f << p;
				}
			}

			f.close();
		};


		/*! 
		\fn     inline void cargarListaFichero(LinkedList<Persona>& lista, const char * fichero)
		\brief  Carga una lista de un fichero
		\param	LinkedList<Persona>& lista
		\param 	const char * fichero
		*/
		inline void cargarListaFichero(LinkedList<Persona>& lista, const char * fichero){

			//Recorrer el fichero guardando cada alumno en un alumno auxiliar, para insertarlo a la lista
			Persona p;
			fstream f;

			f.open(fichero);

			//Recorremos el fichero insertando las personas en la lista

			while(!f.eof){
				f >> p;
					if(p.nombre() != ""){
						lista.insert(p);
					}
			}
			f.close();


		};


#endif