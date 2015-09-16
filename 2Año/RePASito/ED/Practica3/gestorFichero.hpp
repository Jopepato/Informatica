#ifndef GESTORFICHERO_HPP_
#define GESTORFICHERO_HPP_

#include "persona.hpp"
#include <fstream>
#include "edi_LinkedList.hpp"

using namespace std;
using namespace edi;

void listaAFichero(const LinkedList<Persona> &lista, const string & nombreFichero);


void ficheroALista(LinkedList<Persona> &lista, const string & nombreFichero);



#endif