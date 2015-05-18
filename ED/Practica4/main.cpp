/*!
  \file   graph_matrix.cpp
  \brief  Definición de las funciones algoritmicas
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/


#include <iostream>
#include <fstream>
#include <vector>

#include "entrada_salida.hpp"
#include "graph_matrix.hpp"
#include "algoritmos.hpp"
#include "vertex.hpp"
#include "edge.hpp"
	
	using namespace edi;

int main ()
{
	edi::GraphMatrix *g = 0;
	bool cargado = false;
	std::string nombreFicheroGrafo;
	std::string dataProfundidad;
	Vertex origenProfundidad;
	vector<Vertex> encontrados;

	std::cout << "Nombre del fichero grafo: ";
	std::cin >> nombreFicheroGrafo;

	cargado = cargarGrafo(g, nombreFicheroGrafo);
	
	if(cargado)
		mostrarGrafo(*g);
	else
		std::cout << "El grafo no se ha podido cargar\n";

	std::cout << "Dime el nodo por el que quieres hacer profundidad: ";
	std::cin >> dataProfundidad;

	//Ahora buscamos ese nodo en el grafo

	g->searchVertex(dataProfundidad);
	origenProfundidad = g->currVertex();

	//Usamos la funcion de profundidad
	profundidad(*g, origenProfundidad, encontrados);

  return 0;
}
