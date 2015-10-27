#ifndef __EDGE_HPP__
#define __EDGE_HPP__


#include <cassert>

#include  "vertex.hpp"

/*!
\brief Espacio de nombres para la asignatura Estructura de datos.

*/
namespace edi 
{
	/*!\brief Edge of graph.*/
	class Edge
	{
		private:
			double _data; //Weight of the edge
			Vertex _first; //First vertex of the edge
			Vertex _second; //Second vertex of the edge
			
		public:
			const double & getData() const 
			{
				return _data;
			};
			
			const Vertex & first() const 
			{
				return _first;
			};
			
			const Vertex & second() const 
			{
				return _second;
			};
			
			bool has(const Vertex & u) const
			{
				return u == first() or u == second();
			};
			
			//pre-c: has(u) = true
			const Vertex & other(const Vertex & u) const
			{
				assert(has(u));
				if (u == first())
					return second();
				return first();
			};
			
      void setData(const double & data) 
			{
				_data = data;				
			};
			
      void setFirst(const Vertex & first) 
			{
				_first = first;
				
			};
			
      void setSecond(const Vertex & second) 
			{
				_second = second;
			};
			
			bool operator==(const Edge &e)const
			{
				return (e.first() == first() and e.second() == second());
			};
	};

} //namespace ed

#endif
