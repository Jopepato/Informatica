/*!
  \file   graph_matrix.hpp
  \brief  Definición de la clase GraphMatrix
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/

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
\name 	Espacio de nombres de la asignatura de Estructuras de datos y de la información
*/
namespace edi 
{
	//!  Definición de la plantilla de la clase GraphMatrix
	class GraphMatrix
	{
		private:
			vector<Vertex> vectorV_;	//!< Vector of vertexes
			float ** matrixW_;			//!< Adjacency matrix of weights
			bool directed_;				//!< Is directed
			Vertex* vCursor_;			//!< cursor of vertexes
			Edge* eCursor_;				//!< cursor of edges
			unsigned int numVertexes_;	//!< number of vertexes
			unsigned int numEdges_;		//!< number of edges
			unsigned int capacity_;		//!< Capacity of graph (maximum value of _numVertexes. _capacity >= _numVertexes)

		public:


			//! \name Constructores

			/*! 
				\fn        GraphMatrix (const unsigned int & capacity=0, const bool & isDirected = true);
				\brief     Constructor por defecto de la clase GraphMatrix
				\param	   capacity Capacidad del grafo
				\param	   isDirected Es el grafo dirigido o no
			*/

			GraphMatrix (const unsigned int & capacity=0, const bool & isDirected = true);

			//! \name Observadores

			/*!
				\fn		const unsigned int &numVertexes()
				\brief	Observador del campo numVertexes
				\return Valor del atributo numVertexes_
			*/
			inline const unsigned int &numVertexes()const{
				return(numVertexes_);
			};
			/*!
				\fn		const unsigned int &numEdges()
				\brief	Observador del campo numEdges
				\return Valor del atributo numEdges_
			*/

			inline const unsigned int &numEdges()const{
				return (numEdges_);
			};
			/*!
				\fn		const unsigned int &capacity()
				\brief	Observador del campo capacity
				\return Valor del atributo capacity_
			*/			

			inline const unsigned int &capacity()const{
				return(capacity_);
			};
			/*!
				\fn		bool isEmpty()
				\brief	Nos dice sie el grafo esta vacio
				\return Devuelve true si el grafo esta vacio y false en caso contrario
			*/				

			inline bool isEmpty() const{
				//Miramos el numero de nodos
				return(numVertexes_==0);
			}; 
			/*!
				\fn		const bool & isDirected()
				\brief	Nos dice si el grafo es dirigido
				\return Devuelve true si el grafo es dirigido y false en caso contrario
			*/					
			inline const bool & isDirected() const{
				return(directed_);
			};

			/*!
				\fn		const float adjacent(const Vertex & u, const Vertex & v)
				\brief	Devuelve el elemento de la matriz de adyacencia (INFINITO si no hay lado)
				\return Devuelve el elemento de la matriz de adyacencia
				\param u Edge u
				\param v Edge v
			*/				
			
			const float adjacent(const Vertex & u, const Vertex & v) const{

				//Valor a devolver
				float *retVal=NULL;

				retVal = &matrixW_[u.getLabel()][v.getLabel()];

				if(retVal==NULL){
					//Devolvemos infinito
					return(std::numeric_limits<float>::infinity());
					//numeric_limits<float>::infinity()
					//Tambien podemos usar eso
				}

				return(*retVal);

			};

			/*!
				\fn		bool hasCurrVertex()
				\brief	Está el cursor de vértices posición válida
				\return Devuelve true si existe el elemento al que apunta el vCursor
			*/	
			
			inline bool hasCurrVertex() const{
				return(vCursor_!=NULL);
			}; 
			
			/*!
				\fn		const Vertex & currVertex()
				\pre 	hasCurrVertex() is true
				\brief	Devuelve el vértice referenciado por el cursor de vértices
				\return Devuelve el vértice referenciado por cursor de vértices
			*/	
			
			inline const Vertex & currVertex() const{
				return(*vCursor_);
			};
			/*!
				\fn		bool hasCurrEdge()
				\brief	Está el cursor de lados posición válida
				\return Devuelve true si el cursor está en posicion válida y false en otro caso
			*/

			inline bool hasCurrEdge() const{
				//Comprobamos que el cursor apunta a una posicion valida
				return(eCursor_!=NULL);
			};
			
			/*!
				\fn		const Edge currEdge()
				\brief	Miramos si el lado referenciado por el cursor es valido
				\pre 	hasCurrEdge() is true
				\return Devuelve el lado referenciado por cursor de lados
			*/
			inline const Edge currEdge(){
				return(*eCursor_);
			};
			
			//! \name Modificadores

			/*!
				\fn		void makeDirected()
				\brief	Crea un grafo dirigido
			*/			
			
			void makeDirected();
			/*!
				\fn		makeUndirected()
				\brief	Crea un grafo no dirigido
			*/	
			void makeUndirected();

			/*!
				\fn		void addVertex(const std::string & data)
				\pre 	numVertexes() < capacity()
				\brief	Añade un vertice al grafo a partir del data
				\param 	data El dato que le pasamos para que cree el vertice
			*/
			void addVertex(const std::string & data);
			/*!
				\fn 	void addEdge(const double & data, const Vertex & u, const Vertex & v)
				\pre  	u y v pertenecen al grafo
				\brief	Añade un lado a partir de sus dos vértices y su peso. Esto se reflejará sólo en la matriz de adyacencia
				\param	data Peso entre los dos vertices
				\param	u Primer vertice
				\param 	v Segundo vertice
			*/
			void addEdge(const double & data, const Vertex & u, const Vertex & v);
			
			/*!
				\fn 	void searchVertex(const std::string &data)
				\brief  Busca un vertice a partir de su data, colocando el cursor en dicho vértice
				\param	data Peso que debemos buscar
			*/
			void searchVertex(const std::string &data);

			/*!
				\fn		void goTo(const Vertex & u)
				\pre 	u pertenece al grafo
				\brief 	Lleva el cursor a un vertice a partir de dicho vertice
				\param	u Vertice al que queremos llevar el cursor
			*/
			void goTo(const Vertex & u);
			
			/*!
				\fn  	void goTo(const unsigned int &idx)
				\pre 	0 <= idx < numVertexes()
				\brief 	Lleva el cursor a un vértice a partir de la posicion de dicho vertice
				\param 	idx Indice al que queremos llevar el cursor
			*/
			void goTo(const unsigned int &idx);

			/*!
				\fn 	void searchEdge(const Vertex & u, const Vertex & v)
				\brief 	Lleva el cursor a un lado a partir de sus vertices
				\pre 	u y v pertenecen al grafo
				\param 	u Primer nodo del lado que queremos buscar
				\param	v Segundo nodo del lado que queremos buscar
			*/
			void searchEdge(const Vertex & u, const Vertex & v);

			/*!
				\fn 	void beginVertex()
				\brief 	Lleva el cursor al primer vertice
			*/
			void beginVertex();
			
			/*!
				\fn		void nextVertex()
				\brief 	Avanza el cursor al siguiente vertice
			*/
			void nextVertex();

			/*!
				\fn 	bool afterEndVertex()
				\brief 	Comprueba si el cursor ha sobrepasado su última posicion válida
				\return	Devuelve true si lo ha sobrepasado, false en caso contrario
			*/
			bool afterEndVertex() const;

			/*!
				\fn 	void beginEdge(const Vertex & u)
				\brief 	Lleva el cursor al primer lado que sale del vertice u
				\param 	u Vertice del que cogeremos el primer lado que sale de el
			*/
			void beginEdge(const Vertex & u);
			/*!
				\fn 	void nextEdge()
				\brief 	Avanza el cursor al siguiente lado que sale de currEdge().first()
			*/
			void nextEdge();
			
			/*!
				\fn 	bool afterEndEdge()
				\brief	Comprueba si el cursor ha sobrepasado su última posicion válida para los lados que salen de currEdge().first()
				\return Devuelve true en caso de que sea cierto, false en caso contrario
			*/
			bool afterEndEdge();
	};
} //namespace ed

	#endif 