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

	//Muestra una matriz
	void muestraMatriz(int ** matriz, int tam){
		for(int i = 0; i<tam; i++){
			for(int j = 0; j<tam; j++){
				cout << " " << matriz[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Copia una matriz a otra
	void pasaMatriz(float ** matriz, float ** destino, int tam){
		for(int i =0; i<tam; i++){
			for(int j=0; j<tam; j++){
				destino[i][j] = matriz[i][j];
			}
		}
	}

int main ()
{
	edi::GraphMatrix *g = 0;
	bool cargado = false;
	std::string nombreFicheroGrafo;
	std::string dataProfundidad;
	Vertex origenProfundidad;
	vector<Vertex> encontrados;
	float ** distancias;
	int ** intermedios;
	int opcion=0;
	Vertex origen;
	Vertex destino;
	float caminoMin;
	string nodoOrigen, nodoDestino;

	std::cout << "Nombre del fichero grafo: ";
	std::cin >> nombreFicheroGrafo;

	cargado = cargarGrafo(g, nombreFicheroGrafo);
	if(cargado){

	//Reservamos memoria para las dos matrices

	distancias = (float **)malloc(g->capacity()*sizeof(float*));
	for(unsigned int i=0; i<g->capacity(); i++){
		distancias[i] = (float*)malloc(g->capacity()*sizeof(float));
	}

	intermedios = (int **)malloc(g->capacity()*sizeof(int*));
	for(unsigned int i=0; i<g->capacity(); i++){
		intermedios[i] = (int*)malloc(g->capacity()*sizeof(int));
	}

	//Rellenamos con 0 la matriz de intermedios
	for(unsigned int i=0; i<g->capacity(); i++){
		for(unsigned int j=0; j<g->capacity();j++){
			intermedios[i][j] = 0;
		}
	}

	//Pasamos la matriz del grafo a la matriz de distancias
	pasaMatriz(g->matrizW(), distancias, g->capacity());

	while(opcion!=5){


		cout << "1. Imprimir el grafo" << endl;
		cout << "2. Aplicar algoritmo de Floyd" << endl;
		cout << "3. Distancia minima entre dos nodos (primero aplicar Floyd)" << endl;
		cout << "4. Algoritmo de profundidad" << endl;
		cout << "5. Salir" << endl;
		cout << endl;
		cout << "Que opcion desea: ";
		cin >> opcion;
	
	switch(opcion){

	case(1):
			if(cargado){
				mostrarGrafo(*g);

			cout << endl << endl;
			}else{
				std::cout << "El grafo no se ha podido cargar\n";
			}
			break;

			//Pasamos la matriz de adyacencia del grafo a nuestra matriz de distancias


	case(2):
			//Primero aplicamos el algoritmo de floyd y despues mostramos las matrinces
			encontrados.clear();
			floyd(*g, distancias, intermedios);

			cout << "Ahora mostraremos la matriz de intermedios" << endl;
			muestraMatriz(intermedios, g->capacity());

			cout << endl << endl;
			break;


	case(3):
			//Distancia minima entre dos nodos
			cout << "Introduce el nombre del primer nodo: ";
			cin >> nodoOrigen;
			cout << "Introduce el segundo nodo: ";
			cin >> nodoDestino;

			//Buscamos dichos nodos en el grafo y los asociamos
			g->searchVertex(nodoOrigen);
			origen = g->currVertex();
			if(!g->hasCurrVertex()){
				cout << "Nodo 1 seleccionado invalido" << endl;
				break;
			}
			g->searchVertex(nodoDestino);
			destino = g->currVertex();
			if(!g->hasCurrVertex()){
				cout << "Nodo 2 seleccionado invalido" << endl;
				break;
			}

			//Ahora llamamos a la funcion del caminoMinimo
			caminoMin = caminoMinimo(*g, distancias, intermedios, origen, destino);
			cout << nodoDestino << endl;
			cout << "El camino minimo entre " << nodoOrigen << " y " << nodoDestino << " es : " << caminoMin << endl<< endl;

			cout << endl << endl;

			break;


	case(4):
		std::cout << "Dime el nodo por el que quieres hacer profundidad: ";
		std::cin >> dataProfundidad;
		//Limpiamos el vector de explorados
		encontrados.clear();

		//Ahora buscamos ese nodo en el grafo

		g->searchVertex(dataProfundidad);
		origenProfundidad = g->currVertex();

		//Usamos la funcion de profundidad
		profundidad(*g, origenProfundidad, encontrados);

		break;

	case(5):
			cout << "Adios!"<< endl;
			break;
	default:

			std::cout<<"Opcion introducida no valida" << endl << endl << endl;
			break;

	}

}

	  return 0;

}else{
	cout << "No se ha podido cargar el grafo, adios" << endl;
	return 0;
}
}


