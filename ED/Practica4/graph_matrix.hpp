#ifndef __GRAPH_MATRIX_HPP__
#define __GRAPH_MATRIX_HPP__

#include <vector>
#include <iostream>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <cmath>

#include  "edge.hpp"
#include  "vertex.hpp"


using namespace std;

/*!
\brief Espacio de nombres para la asignatura Estructura de datos.

*/
namespace edi 
{

	class GraphMatrix
	{
		private:
			vector<Vertex> vertexes_;	//Vector of vertexes
			float ** matrixW_;			//Adjacency matrix of weights
			bool isDirected_;			//Is directed
			Vertex* vCursor_;			//cursor of vertexes
			Edge* eCursor_;				//cursor of edges
			unsigned int numVertexes_;	//number of vertexes
			unsigned int numEdges_;		//number of edges
			unsigned int capacity_;		//Capacity of graph (maximum value of _numVertexes. _capacity >= _numVertexes)

		public:
			GraphMatrix (const unsigned int & capacity=0, const bool & isDirected = true);


			//Observers

			//Nos devuelve el numero de cosas
			inline const unsigned int &numVertexes()const{
				return(numVertexes_);
			};
			
			//Nos devuelve mas cosas
			inline const unsigned int &numEdges()const{
				return (numEdges_);
			};
			
			//Nos devuelve otras cosas
			inline const unsigned int &capacity()const{
				return(capacity);
			};
			
			//Para comprobar si el grafo esta vacio
			inline bool isEmpty() const{
				//Miramos el numero de nodos
					if(numVertexes_==0)
						return true;
					else
						return false;
			}; 
			
			inline const bool & isDirected() const{
				if(isDirected_)
					return true;
				else
					return false;
			};
			
			//Devuelve el elemento de la matriz de adyacencia (INFINITO si no hay lado)
			const float adjacent(const Vertex & u, const Vertex & v) const{

				//Valor a devolver
				float *retVal;

				retval = &matrixW_[u.getLabel()][v.getLabel()];

				if(retVal==NULL){
					//Devolvemos infinito
					return(INFINITY);
					//numeric_limits<float>::infinity()
					//Tambien podemos usar eso
				}else{
					return(retVal);
				}

			};
			
			//Está el cursor de vértices posición válida
			inline bool hasCurrVertex() const{
				if(vCursor_!=NULL)
					return true;
				else
					return false;
			}; 
			
			//Pre: hasCurrVertex() is true.
			//Devuelve el vértice referenciado por cursor de vértices
			inline const Vertex & currVertex() const{
				assert(hasCurrVertex());
				return(vCursor_);
			};
      
			//Está el cursor de lados posición válida
			inline bool hasCurrEdge() const{
				//Comprobamos que el cursor apunta a una posicion valida
				if(eCursor_!=NULL)
					return true;
				else
					return false;
			};
			
			//Pre: hasCurrEdge() is true
			//Devuelve el lado referenciado por cursor de lados
			inline const Edge currEdge(){
				//Comprobamos que el cursor apunta a una posicion valida
				assert(hasCurrEdge());
				return(eCursor_);
			};
			
			//Modifiers
			
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
      
			//Prec: u pertenece al grafo
			//Lleva el cursor a un vertice a partir de dicho vertice
			void goTo(const Vertex & u);
			
			//Prec: 0 <= idx < numVertexes()
			//lleva el cursor a un vértice a partir de la posicion de dicho vertice
			void goTo(const int &idx);
			
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
