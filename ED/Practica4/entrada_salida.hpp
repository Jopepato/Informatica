#ifndef __ENTRADA_SALIDA_HPP__
#define __ENTRADA_SALIDA_HPP__
#include <iostream>
#include <fstream>
#include "graph_matrix.hpp"

bool cargarGrafo(edi::GraphMatrix * &g, std::string fileGraph);
void mostrarGrafo(edi::GraphMatrix & g);

#endif