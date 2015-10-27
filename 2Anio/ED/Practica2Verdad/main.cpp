/*!
  \file   main.cpp
  \brief  Clase asignatura que contendra el listado de alumnos
  \author Jose Perez-Parras
  \date   4/05/2015
*/


#include "edi_LinkedNode.hpp"
#include "edi_List.hpp"
#include "edi_LinkedList.hpp"
#include "edi_export.hpp"
#include "persona.hpp"
#include "generapersona.hpp"
#include "asignatura.hpp"
#include <iostream>
#include <cstring>

using namespace std;
using namespace edi;

/**
  \mainpage Practica 2, creacion de una Lista
  \author José Pérez-Parras Toledano
  \date 4 de Abril de 2015
*/


/**
  \main Programa principal
  \brief Realiza las llamadas a las funciones para cargar los contornos y calcular el error
*/
int main(){
	int numAlum;
	Persona alumno1, alumno2;
	cout << "Introduce el numero de alumnos: ";
	cin >> numAlum;
	Asignatura ed(numAlum);
	int menu=1;
	ed.VectorALista(generarPersonas("personas.txt", numAlum));

	while(menu!=0){
		
		cout << "0) Salir" << endl;
		cout << "1) Mostrar los alumnos de forma ascendente" << endl;
		cout << "2) Mostrar los alumnos de forma descendente" << endl;
		cout << "3) Mostrar los alumnos entre dos alumnos de forma ascendente" << endl;
		cout << "4) Mostrar los alumnos entre dos alumnos de forma descendente" << endl;
		cout << "5) Modificar un alumno" << endl;
		cout << "Que desea hacer: ";
		cin >> menu;


		switch(menu){


			case 0:
				cout << "Gracias por su visita" << endl;
				break;

			case 1:
				ed.MostrarListaAscendente();
				cout << endl;
				break;

			case 2:
				ed.MostrarListaDescendente();
				cout << endl;
				break;

			case 3:
				cout << "Introduzca los datos del alumno 1:" << endl;
				cin >> alumno1;
				cout << "Introduzca los datos del alumno 2:" << endl;
				cin >> alumno2;
				cout << "Alumnos:" << endl << endl;
				ed.ListadoEntreDosAlumnosAscendente(alumno1, alumno2);
				cout << endl;
				break;

			case 4:

				cout << "Introduzca los datos del alumno 1: " << endl;
				cin >> alumno1;
				cout << "Introduzca los datos del alumno 2: " << endl;
				cin >> alumno2;
				cout << "Alumnos:" << endl << endl;
				ed.ListadoEntreDosAlumnosDescendente(alumno1, alumno2);
				cout << endl;
				break;

			case 5:
				cout << "Introduzca los datos del alumno a modificar" << endl;
				cin >> alumno1;
				cout << "Introduzca los nuevos datos" << endl;
				cin >> alumno2;
				ed.ModificarAlumno(alumno2, alumno1);
				cout << "Alumno modificado" << endl;
				break;

			default:
				cout << "Opcion no valida" << endl;
		}

	}

return 0;
}