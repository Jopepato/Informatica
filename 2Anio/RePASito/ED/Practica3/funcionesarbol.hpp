#ifndef FUNCIONESARBOL_HPP_
#define FUNCIONESARBOL_HPP_

#include "edi_LinkedOrderedBinaryTree.hpp"
#include "persona.hpp"
#include "clave.hpp"
#include "edi_LinkedList.hpp"



void creaArbol(LinkedOrderedBinaryTree<Persona> & arbol,const LinkedList<Persona> lista){
	Clave aux;

	for(int i=0; lista.isValid(i); i++){

		aux.dni(lista.item(i).dni());
		aux.posicion(i);

		arbol.insert(aux);

	}
}



#endif