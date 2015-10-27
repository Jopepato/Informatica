/*!
	\file graph_matrix.cpp
	\date 10/06/2015
	\brief Definicion de los metodos de la clase GraphMatrix
	\author José Pérez-Parras Toledano
*/
#include "graph_matrix.hpp"

using namespace edi;


GraphMatrix::GraphMatrix (const unsigned int & capacity, const bool & isDirected){
	//Reservamos memoria para la matriz y para el vector de vertices

	wMatrix_ = (float **)malloc(capacity*sizeof(float*));

	for(unsigned int i=0; i<capacity; i++){
		wMatrix_[i] = (float*)malloc(capacity*sizeof(float));
	}

	//Rellenamos la matriz con infinito

	for(unsigned int i=0; i<capacity; i++){
		for(unsigned int j=0; j<capacity; j++){
			if(i == j){
				wMatrix_[i][j] = 0;
			}else{
				wMatrix_[i][j] = INFINITY;
			}
		}
	}


	isDirected_ = isDirected;
	currVertex_ = NULL;
	currEdge_ = NULL;
	capacity_ = capacity;
	numVertexes_= 0;
	numEdges_ = 0;

}

const unsigned int GraphMatrix::numVertexes()const{
	return(numVertexes_);
}

const unsigned int GraphMatrix::numEdges()const{
	return(numEdges_);
}

const unsigned int GraphMatrix::capacity()const{
	return(capacity_);
}

bool GraphMatrix::isEmpty() const{
	if(numVertexes_==0)
		return true;
	else
		return false;
}

const bool GraphMatrix::isDirected() const{
	return(isDirected_);
}

const float GraphMatrix::adjacent(const Vertex & u, const Vertex & v) const{

	//Recorremos el vector buscando ambos vertices
	//Cogemos los label de los vertices y buscamos en la matriz :>
	float *aux=NULL;

	*aux = wMatrix_[u.getLabel()][v.getLabel()];

	if(aux == NULL){
		return(INFINITY);
	}else{
		return(*aux);
	}

}

bool GraphMatrix::hasCurrVertex()const{
	return(currVertex_);
}

const Vertex & GraphMatrix::currVertex()const{
	assert(hasCurrVertex());
	return(*currVertex_);
}

bool GraphMatrix::hasCurrEdge() const{
	return(currEdge_);
}

const Edge GraphMatrix::currEdge(){
	assert(hasCurrEdge());
	return(*currEdge_);
}



void GraphMatrix::makeDirected(){
	isDirected_ = true;
}


void GraphMatrix::makeUndirected(){
	isDirected_ = false;
}

void GraphMatrix::addVertex(const std::string & data){
	//Añadimos un vertice al vector
	Vertex aux;
	aux.setData(data);
	aux.setLabel(numVertexes());
	vVertex_.push_back(aux);

	//Aumentamos el numero de vertices
	numVertexes_++;
}
void GraphMatrix::addEdge(const double & data, const Vertex & u, const Vertex & v){
	//Añadimos un lado a la matriz de adyacencia a partir de dos vertices

	//Si es dirigido lo añadimos en una posicion
	//Si no lo es, debemos añadirlo en las dos
	if(isDirected()){
		wMatrix_[u.getLabel()][v.getLabel()] = data;
	}else{
		wMatrix_[u.getLabel()][v.getLabel()] = data;
		wMatrix_[v.getLabel()][u.getLabel()] = data;
	}
	numEdges_++;

}

void GraphMatrix::searchVertex(const std::string &data){
	//Busca un nodo a partir del data

	for(unsigned int i = 0; i<numVertexes(); i++){
		if(vVertex_[i].getData() == data){
			currVertex_ = &vVertex_[i];
		}
	}
}

void GraphMatrix::goTo(const Vertex & u){
	//Busca un nodo a partir de un nodo

	for(unsigned int i =0; i<numVertexes(); i++){
		if(vVertex_[i] == u){
			currVertex_ = &vVertex_[i];
		}
	}
}

void GraphMatrix::goTo(const unsigned int &idx){
	assert(0<=idx && idx<=numVertexes());

	currVertex_ = &vVertex_[idx];
}

void GraphMatrix::searchEdge(const Vertex & u, const Vertex & v){
	//Deberiamos comprobar que u y v estan en el vector :>

	Edge* aux = new Edge;
	aux->setFirst(u);
	aux->setSecond(v);
	aux->setData(wMatrix_[u.getLabel()][v.getLabel()]);

	currEdge_ = aux;
}

void GraphMatrix::beginVertex(){
	currVertex_ = &vVertex_[0];
}

void GraphMatrix::nextVertex(){
	currVertex_++;
}

bool GraphMatrix::afterEndVertex() const{
	if(currVertex_!=&vVertex_[capacity()]){
		return false;
	}else{
		return true;
	}

}


void GraphMatrix::beginEdge(const Vertex & u){
	//Lleva el cursor al primer lado que sale del vertice u :>

	bool encontrado =false;
	Edge* aux = new Edge;
	aux->setFirst(u);
	for(unsigned int j=0; j<capacity(); j++){
		//Buscamos el primer vertice que conecta con el
		if(wMatrix_[u.getLabel()][j]> 0 && wMatrix_[u.getLabel()][j]< INFINITY && encontrado == false){
			encontrado = true;
			aux->setData(wMatrix_[u.getLabel()][j]);
			aux->setSecond(vVertex_[j]);
		}
	}

	if(encontrado){
		currEdge_ = aux;
	}else{
		currEdge_ = NULL;
	}

}


void GraphMatrix::nextEdge(){
	//Lleva el cursor al siguiente lado :>

	bool encontrado = false;
	Edge* aux = new Edge;
	aux->setFirst(currEdge().first());

	for(unsigned int j=currEdge().second().getLabel()+1; j<numVertexes(); j++){

		if(wMatrix_[currEdge().first().getLabel()][j] > 0 && encontrado == false && wMatrix_[currEdge().first().getLabel()][j] < INFINITY){
			aux->setSecond(vVertex_[j]);
			aux->setData(wMatrix_[currEdge().first().getLabel()][j]);
			encontrado = true;
		}

	}

	if(encontrado){
		currEdge_ = aux;
	}else{
		currEdge_ = NULL;
	}
}


bool GraphMatrix::afterEndEdge(){

	if(currEdge_==NULL)
		return true;
	else
		return false;

}