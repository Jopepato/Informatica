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
	searchVertex(u.getData());
	assert(vCursor_!=NULL);
	searchVertex(v.getData());
	assert(vCursor_!=NULL);

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

	for(unsigned int i = 0; i<vectorV_.capacity(); i++){
		
		if(vectorV_[i].getData() == data){
			vCursor_=&vectorV_[i];
		}
	}

};

//Los el vector a un vertice a partir del data
void GraphMatrix::goTo(const Vertex & u){
		//Primero comprobamos que el vertice pertenece
		searchVertex(u.getData());
		assert(vCursor_!=NULL);

		for(unsigned int i=0; i<vectorV_.capacity(); i++){

				if(vectorV_[i].getData() == u.getData()){
					vCursor_ = &vectorV_[i];
				}
		}


};

//lleva el cursor a un vértice a partir de la posicion de dicho vertice
void GraphMatrix::goTo(const int &idx){
	//Comprobamos que el indice esta entre los indices del vector
	assert(0<=idx && idx<numVertexes());

		vCursor_ = &vectorV_[idx];

};

//Lleva el cursor a un lado a partir de sus vertices
void GraphMatrix::searchEdge(const Vertex & u, const Vertex & v){
	//Primero comprobamos que ambos vertices existen
	searchVertex(u.getData());
	assert(vCursor_!=NULL);
	searchVertex(v.getData());
	assert(vCursor_!=NULL);

	eCursor_->setData(matrixW_[u.getLabel()][v.getLabel()]);
	eCursor_->setFirst(u);
	eCursor_->setSecond(v);

};

//Lleva el cursor al primer vertice
void GraphMatrix::beginVertex(){
	vCursor_=&vectorV_[0];
};

//Avanza el cursor al siguiente vertice
void GraphMatrix::nextVertex(){
	vCursor_++;
};

//Comprueba si el cursor ha sobrepasado su última posicion válida
bool GraphMatrix::afterEndVertex() const{

	if(vCursor_!=&vectorV_[capacity()]){
		return true;
	}else{
		return false;
	}

};

//Lleva el cursor al primer lado que sale del vertice u
void GraphMatrix::beginEdge(const Vertex & u){
	bool found = false;
	Edge * aux = eCursor_;
	aux->setFirst(u);

	for(unsigned int i=0; i<capacity() && found == false; i++){

		if(matrixW_[u.getLabel()][i]>0 && matrixW_[u.getLabel()][i]<INFINITY){
			found = true;
			aux->setSecond(vectorV_[i]);
			aux->setData(matrixW_[u.getLabel()][i]);
		}
	}

	if(found == true){
		eCursor_=aux;
	}else{
		eCursor_=NULL;
	}


};

//Avanza el cursor al siguiente lado que sale de currEdge().first()
void GraphMatrix::nextEdge(){
	bool found;
	Edge * aux = eCursor_;

	for(unsigned int i = aux->second().getLabel()+1; i< capacity() && found == false; i++){

		if(matrixW_[aux->first().getLabel()][i]>0 && matrixW_[aux->first().getLabel()][i]<INFINITY){

			aux->setSecond(vectorV_[i]);
			aux->setData(matrixW_[aux->first().getLabel()][i]);
			found = true;
		}
	}
	if(found == true){
		eCursor_=aux;
	}else{
		eCursor_=NULL;
	}

};

//Comprueba si el cursor ha sobrepasado su última posicion válida para los lados que salen de currEdge().first()
bool GraphMatrix::afterEndEdge(){

	if(eCursor_==NULL){
		return true;
	}else{
		return false;
	}

};