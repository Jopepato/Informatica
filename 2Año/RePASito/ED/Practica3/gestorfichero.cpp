#include "gestorfichero.hpp"

void listaAFichero(const LinkedList<Persona> &lista, const string & nombreFichero){

	ofstream fichero;
	fichero.open(nombreFichero.c_str());

	if(fichero.is_open()){
		for(int i=0; lista.isValid(i); i++){
			fichero << lista.item(i);
		}
	}

	fichero.close();
}



void ficheroALista(LinkedList<Persona> &lista, const string & nombreFichero){

	ifstream fichero;
	Persona aux;
	fichero.open(nombreFichero.c_str());

	if(fichero.is_open()){
		while(fichero >> aux){
			lista.inserta(aux);
		}
	}

	fichero.close();

}