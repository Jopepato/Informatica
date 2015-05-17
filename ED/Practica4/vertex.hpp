/*!
  \file   vertex.hpp
  \brief  Definición de la clase Vertex
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/

#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <iostream>
#include <cassert>




/*!
\name Espacio de nombres de la asignatura de Estructuras de datos y de la información.

*/
namespace edi 
{

	//!  Definición de la plantilla de la clase Vertex
	class Vertex
	{
		private:
			std::string _data; //!< 	Data of the vertex
			int _label; //!< 			Label of the vertex
		
		public:
			//! \name Observadores

			/*
				\fn 	const std::string & getData()
				\brief 	Funcion que devuelve el atributo data
				\return Devuelve el atributo _data

			*/
			const std::string & getData()const
			{ 
				return _data;
			}
			
			/*
				\fn 	const int & getLabel()
				\brief 	Funcion que devuelve el atributo label
				\return Devuelve el atributo _label
			*/
			const int & getLabel()const
			{
				return _label;
			}
			
			//! \name Modificadores

			/*
				\fn 	void setData(const std::string &data)
				\brief 	Asigna al atributo _data el valor pasado por parametro
				\param 	data Valor que se le asignara al campo privado _data
			*/
			void setData(const std::string &data)
			{
				_data = data;
			}
			
			/*
				\fn 	void setLabel(const int &label)
				\brief 	Asigna al atributo _label el valor pasado por parametro
				\param 	label Valor que se le asignara al campo privado _label
			*/
			void setLabel(const int &label)
			{
				_label = label;
			}
			
			//! \name Operadores

			/*
				\fn 	bool operator==(const Vertex &v)
				\brief 	Sobrecarga del operador relacional de igualdad
				\param 	v Vertice con el que se va a comparar el vertice actual
				\return Valor logico que indica si el vertice actual es igual que el vertice v
			*/
			bool operator==(const Vertex &v)const
			{
				return (v.getData() == getData());
			}

			/*
				\fn 	bool operator!=(const Vertex &v)
				\brief 	Sobrecarga del operador relacional de distinción	
				\param 	v Vertice con el que ver si hay distincion con el vertice actual
				\return	Valor logico que indica si el vertice actual es distinto al vertice v
			*/
			
			bool operator!=(const Vertex &v)const
			{
				return (v.getData() != getData());
			}
	};
	
	
} //namespace ed

	#endif 
