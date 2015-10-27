/*!
  \file   edge.hpp
  \brief  Definición de la clase Edge
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/
#ifndef __EDGE_HPP__
#define __EDGE_HPP__


#include <cassert>

#include  "vertex.hpp"

/*!
\name Espacio de nombres para la asignatura Estructura de datos.

*/
namespace edi 
{
	//!  Definición de la plantilla de la clase Edge
	class Edge
	{
		private:
			double _data; //!< 		Weight of the edge
			Vertex _first; //!< 	First vertex of the edge
			Vertex _second; //!< 	Second vertex of the edge
			
		public:
			//! \name Obeservadores

			/*!
				\fn		const double & getData()
				\brief 	Funcion que devuelve el atributo privado _data
				\return Valor del atributo _data
			*/
			const double & getData() const 
			{
				return _data;
			}

			/*!
				\fn		const Vertex & first()
				\brief 	Funcion que devuelve el atributo privado _first
				\return Valor del atributo _first
			*/			
			const Vertex & first() const 
			{
				return _first;
			}

			/*!
				\fn		const Vertex & second()
				\brief 	Funcion que devuelve el atributo privado _second
				\return Valor del atributo _second
			*/				
			const Vertex & second() const 
			{
				return _second;
			}
			
			/*!
				\fn 	bool has(const Vertex & u)
				\brief	Funcion que comprueba si un vertice pasado por parametro pertenece a este lado
				\param 	u Vertice para saber si pertenece a este lado
				\return	Valor lógico, que nos devolverá true si ese vertice pertenece a este lado y false en caso contrario
			*/
			bool has(const Vertex & u) const
			{
				return u == first() or u == second();
			}
			
			/*!
				\fn 	const Vertex & other(const Vertex & u)
				\brief 	Funcion que nos devuelve el segundo vertice de este lado si le pasamos el primero
				\pre 	has(u) = true
				\param 	u Vertice que comprobaremos que existe en este lado, para proporcionar el otro
				\return	Vertice del lado
			*/
			const Vertex & other(const Vertex & u) const
			{
				assert(has(u));
				if (u == first())
					return second();
				return first();
			}
			
			//! \name Modificadores

			/*!
				\fn 	void setData(const double & data)
				\brief 	Asigna al atributo privado _data el valor pasado por parametro
				\param 	data Parametro que se le asignara al atributo privado _data
			*/
		     void setData(const double & data) 
			{
				_data = data;				
			}
			
			/*!
				\fn 	void setFirst(const Vertex & first)
				\brief 	Asigna al atributo privado _first el valor pasado por parametro
				\param 	first Parametro que se le asignara al atributo privado _first
			*/
		    void setFirst(const Vertex & first)
			{
				_first = first;		
			}

			/*!
				\fn 	void setSecond(const Vertex & second) 
				\brief 	Asigna al atributo privado _second el valor pasado por parametro
				\param 	second Parametro que se le asignara al atributo privado _second
			*/	
		    void setSecond(const Vertex & second) 
			{
				_second = second;
			}
			
			//! \name Operadores

			/*! 
				\fn     bool operator==(const Edge &e)
				\brief  Sobrecarga del operador relacional de igualdad
				\param  e Lado con el que se va a comparar a el Lado actual
				\post   El valor devuelto debe ser true si el Lado actual es igual al lado e y false en caso contrario
				\return Valor lógico que indica si el Lado actual es igual que el Lado e
			*/
			bool operator==(const Edge &e)const
			{
				return (e.first() == first() and e.second() == second());
			}
	};

} //namespace ed

#endif
