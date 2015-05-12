#include <iostream>
#include <fstream>
#include "graph_matrix.hpp"
#include "entrada_salida.hpp"

using namespace edi;

bool cargarGrafo(edi::GraphMatrix * &g, std::string fileGraph)
{
	std::ifstream f(fileGraph.c_str()); //Se define el stream de lectura y se abre el fichero.
	if (not f)
		return false;
	
  //Se definen variables auxiliares para cargar el grafo.
  unsigned int vertexes;
  int type;
	bool isDirected;
	std::string dataVertex;
	std::string dataEdgeFirst, dataEdgeSecond;
	edi::Vertex first, second;
	double weight;
	
  f >> vertexes; //Se lee el numero de nodos.
  f >> type; //Se lee el tipo.
  
  if (type == 0)
		isDirected = false;
	else
		isDirected = true;
	
	std::cout << "cargados tipo y numero de nodos\n";

  g = new edi::GraphMatrix (vertexes, isDirected); //Se reserva espacio para el grafo y se invoca al constructor.
	
	//Lectura de los data de los nodos
	for(unsigned int i = 1; i <= vertexes; i++)
	{
		f >> dataVertex;
		g->addVertex(dataVertex);
	}
	
	std::cout << "Cargados nodos\n";
	//Lectura de los lados.
	
	//Inicializamos todos los lados a infinito y después se sobreescriben

	while(f >> dataEdgeFirst >> dataEdgeSecond >> weight )
	{
		//Creamos los nodos que forman parte del lado
		//std::cout << "Cargo Lado\n";
		//Para localizar el indice del nodo
		g->searchVertex(dataEdgeFirst);
		first.setLabel((g->currVertex()).getLabel()); 
		
		first.setData(dataEdgeFirst);
		
		//Para localizar el indice del nodo
		g->searchVertex(dataEdgeSecond);
		second.setLabel((g->currVertex()).getLabel());
		
		second.setData(dataEdgeSecond);
		
		//std::cout << "Buscados nodos del lado \n";
		
		//Añade el lado(first, second) con peso weight;
		g->addEdge(weight, first, second);
		
		//std::cout << "Lado añadido \n";
	}
	f.close();
	
	std::cout << "Cargados lados\n";
	
	return true;
}


void mostrarGrafo(edi::GraphMatrix & g)
{	
	g.beginVertex();
	std::cout << "Nodos del grafo\n";
	std::cout << "===============\n";
	
	edi::Vertex v;
	
	do
	{
		v = g.currVertex();
		std::cout << v.getData() << std::endl;
		g.nextVertex();
	}while(not g.afterEndVertex());
	
	//Lados del grafo
	std::cout << "\nLados del grafo\n";
	std::cout << "===============\n";
	std::cout << " Lados = " << g.numEdges() << std::endl;

	edi::Vertex aux;
	g.beginVertex();

	while(not g.afterEndVertex())
	{
		aux = g.currVertex();
		
		g.beginEdge(aux); //Se posiciona en el primer lado que tiene a aux como nodo origen
		while (not g.afterEndEdge())
		{
			std::cout << g.currEdge().first().getData() << ", " << g.currEdge().second().getData() << ", " << g.currEdge().getData() << std::endl;
			g.nextEdge();
		}
		g.nextVertex();
	}
}
	
