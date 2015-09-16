#ifndef __GRAPH_MATRIX_HPP__
#define __GRAPH_MATRIX_HPP__

#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include  "edge.hpp"
#include  "vertex.hpp"

/*!
\brief Espacio de nombres para la asignatura Estructura de datos.

*/
using namespace std;

namespace edi 
{

	class GraphMatrix
	{
		private:
			vector<Vertex> vVertex_;		//!< Vector of vertexes
			float ** wMatrix_;				//!< Adjacency matrix of weights
			bool isDirected_;				//!< Is directed
			Vertex * currVertex_;			//!< cursor of vertexes
			Edge * currEdge_;				//!< cursor of edges
			unsigned int numVertexes_;		//!< number of vertexes
			unsigned int numEdges_;			//!< number of edges
			unsigned int capacity_;			//!< Capacity of graph (maximum value of _numVertexes. _capacity >= _numVertexes)

		public:
			/*!
				\name Constructor
			*/

			GraphMatrix (const unsigned int & capacity=0, const bool & isDirected = true);


			/*!
				\name Oberservers
			*/
			const unsigned int numVertexes()const;
			
			const unsigned int numEdges()const;
			
			const unsigned int capacity()const;
			
			bool isEmpty() const; 
			
			const bool  isDirected() const;
			
			//Devuelve el elemento de la matriz de adyacencia (INFINITO si no hay lado)
			const float adjacent(const Vertex & u, const Vertex & v) const;
			
			//Está el cursor de vértices posición válida
			bool hasCurrVertex() const; 
			
			//Pre: hasCurrVertex() is true.
			//Devuelve el vértice referenciado por cursor de vértices
			const Vertex & currVertex() const;
      
			//Está el cursor de lados posición válida
			bool hasCurrEdge() const;
			
			//Pre: hasCurrEdge() is true
			//Devuelve el lado referenciado por cursor de lados
			const Edge currEdge();
			
			/*!
				\name Modifiers
			*/
			
			//Crea un grafo dirigido
			void makeDirected();
			
			//Crea un grafo no dirigido
			void makeUndirected();

			//Prec: numVertexes() < capacity()
			//Añade un vertice al grafo a partir del data
			void addVertex(const std::string & data);

			//Prec: u y v pertenecen al grafo
			//Añade un lado al grafo a partir de sus dos vértices y su peso. Esto se reflejará sólo en la matriz de adyacencia
			void addEdge(const double & data, const Vertex & u, const Vertex & v);
					
			//Busca un vertice a partir de su data, colocando el cursor en dicho vértice
			void searchVertex(const std::string &data);

			float ** matrizW(){
				return(wMatrix_);
			}
      
			//Prec: u pertenece al grafo
			//Lleva el cursor a un vertice a partir de dicho vertice
			void goTo(const Vertex & u);
			
			//Prec: 0 <= idx < numVertexes()
			//lleva el cursor a un vértice a partir de la posicion de dicho vertice
			void goTo(const unsigned int &idx);
			
			//Prec: u y v pertenecen al grafo
			//Lleva el cursor a un lado a partir de sus vertices
			void searchEdge(const Vertex & u, const Vertex & v);

			
			//Vertex cursor
			//Lleva el cursor al primer vertice
			void beginVertex();
			
			//Avanza el cursor al siguiente vertice
			void nextVertex();
			
			//Comprueba si el cursor ha sobrepasado su última posicion válida
			bool afterEndVertex() const;	
			
			//Edge cursor
			//Lleva el cursor al primer lado que sale del vertice u
			void beginEdge(const Vertex & u);
			
			//Avanza el cursor al siguiente lado que sale de currEdge().first()
			void nextEdge();
			
			//Comprueba si el cursor ha sobrepasado su última posicion válida para los lados que salen de currEdge().first()
			bool afterEndEdge();
	};
} //namespace ed

	#endif 
