/*!
  \file   entrada_salida.hpp
  \brief  Declaración de las funciones de entrada/salida del grafo
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/

#ifndef __ENTRADA_SALIDA_HPP__
#define __ENTRADA_SALIDA_HPP__
#include <iostream>
#include <fstream>
#include "graph_matrix.hpp"

 /**
	\fn 	bool cargarGrafo(edi::GraphMatrix * &g, std::string fileGraph)
	\brief 	Carga un grafo a partir de un fichero donde vienen especificados sus nodos y sus lados
	\param	g Grafo de la clase GraphMatrix donde se almacenará el grafo cargado
	\param	fileGraph Nombre del fichero donde viene declarado el grafo a cargar
	\return Devuelve true en caso de que se haya cargado el grafo con exito y false en caso contrario
 */
bool cargarGrafo(edi::GraphMatrix * &g, std::string fileGraph);

/**
	\fn 	void mostrarGrafo(edi::GraphMatrix & g)
	\brief 	Muestra el grafo pasado por parametro por pantalla
	\param 	g Grafo de la clase GraphMatrix que queremos mostrar por pantalla
*/
void mostrarGrafo(edi::GraphMatrix & g);

#endif
