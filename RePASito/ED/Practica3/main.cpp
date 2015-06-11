/*!
  \file   main.cpp
  \brief  Programa que prueba la clase Persona
  \author Name
  \date   16/03/2015
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "persona.hpp"
#include "generarpersona.hpp"
#include "clave.hpp"
#include "asignatura.hpp"
#include "edi_LinkedList.hpp"

using namespace edi;
using namespace std;
/*! 
	\fn     int main()
	\brief  Progra princial
	\return Valor de control
*/
int main()
{
	srand(time(0));
	int numeroPersonas;
	Persona p;
	string fichero = "personas.txt";
	
	vector <edi::Persona> personas;
	
	cout <<" Personas a generar: ";
	cin >> numeroPersonas;
	
	ofstream f(fichero.c_str());
	
	for(int i = 1; i <= numeroPersonas ; i++)
	{
		p = generarPersona();
		cout << p;
		f << p;
	}
	
	f.close();
	
	personas = generarPersonas(fichero, 20);
	Persona aux;
	
	unsigned int minimo = 0;
	
	for(unsigned int i = 0; i <= personas.size() -2; i++)
	{
		minimo = i;
		for(unsigned int j = i + 1; j <= personas.size() -1; j++)
	  {
			if (personas[j] < personas[minimo])
				minimo = j;
		}
		aux = personas[minimo];
		personas[minimo] = personas[i];
		personas[i] = aux;
	}
		
		
	for(unsigned int i = 0; i < personas.size(); i++)
	{
		cout << i + 1 << ". ";
		cout << personas[i];
	}	
	
	return 0;
}

	
