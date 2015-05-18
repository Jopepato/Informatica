/*!
  \file   algoritmos.hpp
  \brief  Declaración de las funciones algoritmicas
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/

#ifndef ALGORITMOS_H_
#define ALGORITMOS_H_

#include "graph_matrix.hpp"
#include "edge.hpp"
#include "vertex.hpp"


//Floyd

  /*
		\fn 	void floyd(GraphMatrix *g, float *** distancias, int *** intermedios)
		\brief	Funcion que aplica el algoritmo de floyd a un grafo y rellena las matrices de distancias e intermedios
		\param 	g Grafo de tipo GraphMatrix sobre el que se realizará el algoritmo de Floyd
		\param	distancias Matriz de tipo float en la que se almacenaran las distancias
		\param 	intermedios Matriz de tipo int en la que se almacenaran los nodos intermedios
  */
  void floyd(GraphMatrix *g, float *** distancias, int *** intermedios);

  /*
		\fn 	void caminoMinimo(GraphMatrix *g, float *** diatancias, int *** intermedios, const Edge * origen, const Edge * destino)
		\brief 	Funcion que gracias al algoritmo de Floyd puede darnos el camino minimo entre dos nodos
		\param	g Grafo de tipo GraphMatrix
		\param 	distancias Matriz de tipo float que almacena las distancias halladas con el algoritmo de Floyd
		\param 	intermedios Matriz de tipo int que almacena los nodos intermedios hallados con el algoritmo de Floyd
		\param 	origen Nodo de tipo Vertex desde el que queremos iniciar el camino
		\param 	destino Nodo de tipo Vertex hasta el que se desea llegar

  */

  void caminoMinimo(GraphMatrix *g, float *** diatancias, int *** intermedios, const Vertex * origen, const Vertex * destino);

  /*
		\fn 	void profundidad(GraphMatrix *g, Vertex * origen)
		\brief	Realiza el recorrido en profundidad desde un nodo, mostrando por los nodos por los que va pasando
		\param 	g Grafo de tipo GraphMatrix, sera el grafo a trabajar
		\param 	origen Nodo de tipo Vertex desde el cual se iniciara el algoritmo de profundidad
  */

  void profundidad(GraphMatrix *g, Vertex * origen);

















#endif