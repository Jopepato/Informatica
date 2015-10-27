#include "funciones.hpp"


using namespace std;

namespace edi{


//No va :( 
void profundidad(GraphMatrix & g, const Vertex & origen, vector<Vertex> & encontrados){

	//Metemos el nodo en el vector de encontrados
	g.beginEdge(origen);
	encontrados.push_back(origen);
	bool encontrado=false;;

	//Imprimimos el origen
	cout << origen.getData() << endl;


	if(encontrados.size()>=g.numVertexes()){
		cout << "Fin de grafo" << endl;
	}else{
	cout << "Adios" << endl;
	while(encontrados.size()<=g.numVertexes()){
		//Miramos si el lado esta en el vector, si no es asi llamamos a la funcion para que lo meta
		for(unsigned int i=0; i<g.numVertexes(); i++){
			cout << "hola" << i << endl;
			if(encontrados[i] == g.currEdge().second()){
				encontrado = true;
			}
		}
		if(!encontrado){
			cout << "profundidad" << endl;
			profundidad(g, g.currEdge().second(), encontrados);

		}

		g.nextEdge();
		//Si esta pasamos al siguiente nodo.
	}

	}
}


void floyd(GraphMatrix & g, float ** intermedios, float ** distancias){
	//Tenemos que rellenar la matriz de distancias y la de intermedios

	float suma;
	//la matriz de distancias deberia ser la matriz de adyacencia del grafo

	for(unsigned int k=0; k<g.numVertexes(); k++){
		for(unsigned int i=0; i<g.numVertexes(); i++){
			for(unsigned int j=0; j<g.numVertexes(); j++){
				if(distancias[i][k] == INFINITY || distancias[k][j] == INFINITY){
					suma = INFINITY;
				}else{
					suma = distancias[i][k] + distancias[k][j];
				}

			if(distancias[i][j] > suma){
				distancias[i][j] = suma;
				intermedios[i][j] = k;
			}


			}
		}
	}

}



void caminoMin(GraphMatrix &g,float ** intermedios, float ** distancias, const Vertex & origen, const Vertex & destino){

	unsigned int label;
	Vertex aux;

	//Miramos si no tiene intermedios

	//Esto es que no existe nodo intermedio y estan interconectados a tiempo y armonizados
	if(intermedios[origen.getLabel()][destino.getLabel()] == INFINITY){
		cout << origen.getData() << "---";
	}else{
		//Aqui comienza el bucle
		label=intermedios[origen.getLabel()][destino.getLabel()];
		g.goTo(label);
		aux = g.currVertex();

		//Llamamos a la funcion para que vaya hacia las dos partes
		caminoMin(g, intermedios, distancias, origen, aux);
		caminoMin(g, intermedios, distancias, aux, destino);

	}



}






}