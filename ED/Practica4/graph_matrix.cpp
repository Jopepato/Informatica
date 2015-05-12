#include "graph_matrix.hpp"

//Aqui haremos las funciones del archivo graph_matrix.hpp

using namespace edi;

//Aqui definimos el constructor y los modificadores

GraphMatrix::GraphMatrix(const unsigned int & capacity, const bool & isDirected){

	capacity_ = capacity;

	//Reservamos memoria para la matriz
	matrixW_=(float **)malloc(capacity*sizeof(float *));

	for(unsigned int i=0; i< capacity; i++){
		matrixW_[i]=(float*)malloc(capacity*sizeof(float));
	} 

	//Ahora lo rellenamos, con 0 cuando el camino es de un nodo a si mismo y con inf en los otros casos
	for(unsigned int i= 0; i<capacity; i++){
		for(unsigned int j=0; j<capacity; j++){
			if(i==j){
				matrixW_[i][j] = 0;
			}else{
				matrixW_[i][j] = INFINITY;
				//numeric_limits<float>::infinity()
			}
		}
	}

	directed_ = isDirected;
	vCursor_ = NULL;
	eCursor_ = NULL;
	numVertexes_ = 0;
	numEdges_ = 0;

};


//Modifiers

//Hacemos un grafo dirigido
void GraphMatrix::makeDirected(){

};

//Hacemos un grafo no dirigido
void GraphMatrix::makeUndirected(){

};

//Añadimos un Vertex
void GraphMatrix::addVertex(const std::string & data){

};

//Añadimos un Edge
void GraphMatrix::addEdge(const double & data, const Vertex & u, const Vertex & v){

};

//Buscamos un Vertex
void GraphMatrix::searchVertex(const std::string &data){

};

void GraphMatrix::goTo(const Vertex & u){

};


void GraphMatrix::goTo(int &idx){

};

void GraphMatrix::searchEdge(const Vertex & u, const Vertex & v){

};

void GraphMatrix::beginVertex(){

};

void GraphMatrix::nextVertex(){

};

bool GraphMatrix::afterEndVertex() const{

};

void GraphMatrix::beginEdge(const Vertex & u){

};

void GraphMatrix::nextEdge(){

};

bool GraphMatrix::afterEndEdge(){

};