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
	vectorV_.clear();

};


//Modifiers

//Hacemos un grafo dirigido
void GraphMatrix::makeDirected(){
	directed_=true;
};

//Hacemos un grafo no dirigido
void GraphMatrix::makeUndirected(){
	directed_=false;
};

//Añadimos un Vertex a partir del data
void GraphMatrix::addVertex(const std::string & data){
	assert(numVertexes_<capacity_);
	Vertex v;
	v.setData(data);
	v.setLabel(numVertexes_);
	vectorV_.push_back(v);
	numVertexes_++;
};

//Añadimos un Edge
void GraphMatrix::addEdge(const double & data, const Vertex & u, const Vertex & v){
	//Comprobamos que u y v pertenecen al grafo
	assert(searchVertex(u.data) && vCursor_=NULL);
	assert(searchVertex(v.data) && vCursor_=NULL);

	//Ahora añadimos, si es dirigido en una sola posicion y si no lo es, en las dos
	if(directed_){
		matrixW_[u.getLabel()][v.getLabel()] = data;
	}else{
		matrixW_[u.getLabel()][v.getLabel()] = data;
		matrixW_[v.getLabel()][u.getLabel()] = data;
	}

	numEdges_++;

};

//Buscamos un Vertex en el vector de Vertexes y colocamos el cursor apuntandole a el
void GraphMatrix::searchVertex(const std::string &data){
	bool found = false;

	for(unsigned int i = 0; i<vectorV_.capacity(), i++){
		
		if(vectorV_[i].getData() == data){
			vCursor_=&vectorV_[i];
			found= true;
		}
	}

	return found;

};

//Los GoTo estan wapens
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