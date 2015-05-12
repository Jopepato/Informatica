#include <iostream>
#include <fstream>

#include "graph_matrix.hpp"
#include "entrada_salida.hpp"
	
int main ()
{
	edi::GraphMatrix *g = 0;
	bool cargado = false;
	std::string nombreFicheroGrafo;

	std::cout << "Nombre del fichero grafo: ";
	std::cin >> nombreFicheroGrafo;

	cargado = cargarGrafo(g, nombreFicheroGrafo);
	
	if(cargado)
		mostrarGrafo(*g);
	else
		std::cout << "El grafo no se ha podido cargar\n";
  
  return 0;
}
