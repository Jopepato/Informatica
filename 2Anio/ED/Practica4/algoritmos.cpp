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
  	g.beginEdge(origen);
  	encontrados.push_back(origen);

	cout << origen.getData() << endl;

	//*aux = g.currEdge();
	
	if(encontrados.size()>=g.numVertexes()){
		cout << "Fin de grafo" << endl;
	}else{

		  //Hacemos un bucle para ir pasando por sus vertices
		  while((!g.afterEndVertex()) && (encontrados.size()<=g.numVertexes())){	

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

  void floyd(GraphMatrix &g, float ** distancias, int ** intermedios){
    float suma;
    int n=g.capacity();

    for(int i = 0; i < n; i++){
        //Rellenamos la diagonal con 0 puesto que son las relaciones de los nodos con ellos mismos
        distancias[i][i] = 0;

    }
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                
              if(distancias[i][k]==std::numeric_limits<float>::infinity() || distancias[k][j]==std::numeric_limits<float>::infinity()){ 
                    suma=std::numeric_limits<float>::infinity();
               }else{ 
                  suma = distancias[i][k] + distancias[k][j];
               }
                if(suma < distancias[i][j]){
                      distancias[i][j] = suma;
                      intermedios[i][j]= k;
              }
            }
          
        


  }


  float caminoMinimo(GraphMatrix &g, float ** distancias, int ** intermedios, const Vertex & origen, const Vertex & destino){

    //Primero comprobamos que ambos nodos estan en el grafo
    float suma=0;
        Vertex aux;
        unsigned int label;


        if(intermedios[origen.getLabel()][destino.getLabel()]==0){
              //Quiere decir que estamos ante dos nodos que no tienen intermedio
              cout << origen.getData() << "---";
              return(distancias[origen.getLabel()][destino.getLabel()]);
        }else{
          label = intermedios[origen.getLabel()][destino.getLabel()];
          g.goTo(label);
          aux = g.currVertex();

          suma += caminoMinimo(g, distancias, intermedios, origen, aux);

          suma += caminoMinimo(g, distancias, intermedios, aux, destino);

          return(suma);
        }


  }


}//namespace edi