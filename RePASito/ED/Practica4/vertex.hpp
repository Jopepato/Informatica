#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <iostream>
#include <cassert>




/*!
\brief Espacio de nombres para la asignatura Estructura de datos.

*/
namespace edi 
{

	/*!\brief Vertex of Graph.*/
	class Vertex
	{
		private:
			std::string _data; //Data of the vertex
			int _label; //Label of the vertex
		
		public:
			const std::string & getData()const
			{ 
				return _data;
			};
			
			const int & getLabel()const
			{
				return _label;
			};
			
			void setData(const std::string &data)
			{
				_data = data;
			};
			
			void setLabel(const int &label)
			{
				_label = label;
			};
			
			bool operator==(const Vertex &v)const
			{
				return (v.getData() == getData());
			};
			
			bool operator!=(const Vertex &v)const
			{
				return (v.getData() != getData());
			};
	};
	
	
} //namespace ed

	#endif 
