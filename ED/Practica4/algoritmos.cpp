/*!
  \file   graph_matrix.cpp
  \brief  Definición de las funciones algoritmicas
  \author José Pérez-Parras Toledano
  \date   16/05/2015
*/

#include "algoritmos.hpp"

namespace edi{

  void profundidad(GraphMatrix &g, const Vertex & origen, vector<Vertex>& encontrados){

  	//Metemos el nodo que nos dan en el vector de encontrados
  	//Edge *aux = new Edge;
  	g.beginEdge(origen);
  	encontrados.push_back(origen);

	cout << origen.getData() << endl;

	//*aux = g.currEdge();
	
	if(encontrados.size()>=g.capacity()){
		cout << "Fin de grafo" << endl;
	}else{

		  //Hacemos un bucle para ir pasando por sus vertices
		  while((!g.afterEndVertex()) && (encontrados.size()<=g.capacity())){

		  		//*aux = g.currEdge();  		

		  		//Ahora tenemos que mirar si ya estaba en encontrados
		  		if(!compruebaEncontrados(g.currEdge().second(), encontrados)){
		  			//Si no esta lo llamamos
		  			profundidad(g, g.currEdge().second(), encontrados);
		  		}
		  		//Nos vamos al siguiente lado
		  		g.nextEdge();

		  }
}

  }

  bool compruebaEncontrados(const Vertex & u,vector<Vertex> & encontrados){
  	//Comprueba si un nodo esta en encontrados

  	for(unsigned int i =0; i<encontrados.capacity(); i++){
  		if(u == encontrados[i]){
  			return true;
  		}
  	}

  	return false;

  }

  void floyd(GraphMatrix *g, float ** distancias, int ** intermedios){



  }


  void caminoMinimo(GraphMatrix *g, float ** diatancias, int ** intermedios, const Vertex * origen, const Vertex * destino){



  }

}