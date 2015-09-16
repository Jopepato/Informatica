/*!
  \file   generarpersona.hpp
  \brief  Prototipos de las funciones auxiliares para generar aleatoriamente personas
  \author Name
  \date   16/03/2015
*/

#ifndef _GENERAR_PERSONA_HPP_
#define _GENERAR_PERSONA_HPP_
#include <vector>

#include "persona.hpp"

/*! 
	\fn     Persona generarPersona();
	\brief  Genera aleatoriamente una Persona
	\return Objeto de la clase Persona
	\pre    Ninguna
	\post   La Persona devuelta debe existir
	\sa     generarPersonas
*/
edi::Persona generarPersona();


/*! 
	\fn     vector <Persona> generarPersonas(char *fichero, int numeroPersonas);
	\brief  Genera aleatoriamente un vector de Personas
	\param	fichero Nombre del fichero desde el que se van a leer datos de personas
	\param	numeroPersonas Número de personas que se van a generar
	\return Vector STL de objetos de la clase Persona
	\pre    El fichero debe existir
	\pre	numeroPersonas debe ser un número natural
	\post   El número de componentes del vector devuelto debe ser igual a numeroPersonas
	\sa     generarPersona
*/
std::vector <edi::Persona> generarPersonas(const char *fichero,const int &numeroPersonas);

#endif //_GENERAR_PERSONA_HPP_
