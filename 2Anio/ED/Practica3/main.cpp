/*!
  \file   main.cpp
  \brief  Programa que prueba la clase Persona
  \author Name
  \date   16/03/2015
*/
#include "edi_LinkedNode.hpp"
#include "edi_List.hpp"
#include "edi_LinkedList.hpp"
#include "edi_exports.hpp"
#include "listaFichero.hpp"
#include "generapersona.hpp"
#include "asignatura.hpp"
#include "clave.hpp"
#include "edi_LinkedOrderedBinaryTree.hpp"


using namespace edi;
using namespace std;


/*! 
	\fn     int main()
	\brief  Progra princial
	\return Valor de control
*/
int main()
{

	LinkedList<Clave> claves;
	LinkedList<Persona> alumnos;

	int nAlum;
	int opcion;
	char * fichero;

	cout << "Numero de alumnos: " << endl;
	cin >> nAlum;
	Asignatura historia(nAlum);

	historia.VectorALista(generarPersonas("personas.txt", nAlum));


	int menu= 1;

	while(menu!=0){


		cout << "1.- Guardar la lista en un fichero" << endl;
		cout << "2.- Cargar la lista de un fichero" << endl;

		cout << "Que desea: ";
		cin >> opcion;


		switch(opcion){


			case 1:
				int caso;
					cout << "Desea guardar la lista de alumnos? 1- si 2-no" << endl;
					cin >> caso;
					if(caso==1){
						guardarListaFichero(historia.getLista(), "fichero.txt");
					}else{
						guardarListaFichero(alumnos, "alumnos.txt");
					}

				break;


			case 2:
				cargarListaFichero(alumnos, "alumnos.txt");
				cout << "Ü" << endl;
				break;


			default:
					cout << "Se equivoco :<" << endl;
				break;



		}


	}

	return 0;
}

	
