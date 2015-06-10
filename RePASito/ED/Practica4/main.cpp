#include <iostream>
#include <fstream>
#include <vector>

#include "entrada_salida.hpp"
#include "graph_matrix.hpp"
#include "funciones.hpp"
#include "vertex.hpp"
#include "edge.hpp"
using namespace edi;
using namespace std;


void pasarMatriz(float ** origen, float ** destino, int tam){
	for(int i=0; i<tam; i++){
		for(int j=0; j<tam; j++){
			destino[i][j] = origen[i][j];
		}
	}
}

void muestraMatriz(float ** matriz, int tam){
	for(int i=0; i<tam; i++){
		cout << endl;
		for(int j=0; j<tam; j++){
			cout << " " << matriz[i][j] << " ";
		}
	}
}

int main ()
{
	edi::GraphMatrix *g = 0;
	bool cargado = false;
	Vertex origen;
	Vertex destino;
	string dataOrigen;
	string dataDestino;
	vector<Vertex> encontrados;
	std::string nombreFicheroGrafo;
	float ** intermedios;
	float ** distancias;





	std::cout << "Nombre del fichero grafo: ";
	std::cin >> nombreFicheroGrafo;

	cargado = cargarGrafo(g, nombreFicheroGrafo);
	
	if(cargado)
		mostrarGrafo(*g);
	else
		std::cout << "El grafo no se ha podido cargar\n";

	//Primero tenemos que reservar memoria para ambas matrices
	intermedios = (float**)malloc(g->numVertexes()*sizeof(float*));
	for(unsigned int i=0; i<g->numVertexes(); i++){
		intermedios[i] = (float*)malloc(g->numVertexes()*sizeof(float));
	}

	distancias = (float**)malloc(g->numVertexes()*sizeof(float*));
	for(unsigned int i=0; i<g->numVertexes(); i++){
		distancias[i] = (float*)malloc(g->numVertexes()*sizeof(float));
	}



	//Rellenamos la matriz de intermedios con infinitos
	for(unsigned int i=0; i<g->numVertexes(); i++)
		for(unsigned int j=0; j<g->numVertexes(); j++){
			intermedios[i][j] = INFINITY;
		}

	//Pasamos la matriz de distancias del grafo a otra matriz

  /*
	cout << "Introduce el grafo por el que empezar la profundidad" << endl;
	cin >> data;

	g->searchVertex(data);
	origen = g->currVertex();

	profundidad(*g, origen, encontrados);
	*/

	//Hacemos floyd y mostramos la matriz
	muestraMatriz(g->matrizW(), g->numVertexes());
	cout << endl;

	pasarMatriz(g->matrizW(), distancias, g->numVertexes());

	floyd(*g, intermedios, distancias);

	muestraMatriz(distancias, g->numVertexes());

	cout << endl;

	//Ahora el camino minimo

	cout << "Introduce el nodo origen: ";
	cin >> dataOrigen;
	cout << "Introduce el nodo destino: ";
	cin >> dataDestino;

	g->searchVertex(dataOrigen);
	origen = g->currVertex();
	g->searchVertex(dataDestino);
	destino = g->currVertex();

	//Ahora llamamos a la funcion

	caminoMin(*g, intermedios, distancias, origen, destino);
	cout << dataDestino << endl;


  return 0;
}
