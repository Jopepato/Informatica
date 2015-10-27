/*!
	\file funciones.hpp
	\brief Declaracion de las funciones del grafo
	\date 10/06/2015
	\name José Pérez-Parras Toledano
*/

#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_


#include <iostream>
#include <cassert>
#include <cstdlib>
#include "graph_matrix.hpp"
#include "vertex.hpp"
#include "edge.hpp"


//Declaramos las funciones

namespace edi{


void profundidad(GraphMatrix & g, const Vertex & origen, vector<Vertex> & encontrados);

void floyd(GraphMatrix & g, float ** intermedios, float ** distancias);

void caminoMin(GraphMatrix &g,float ** intermedios, float ** distancias, const Vertex & origen, const Vertex & destino);


}


#endif