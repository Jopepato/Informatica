#include "graph_matrix.hpp"

//Aqui haremos las funciones del archivo graph_matrix.hpp

using namespace edi;

//Aqui definimos el constructor y los modificadores

GraphMatrix::GraphMatrix(){

};


//Modifiers

void GraphMatrix::makeDirected(){

};

void GraphMatrix::makeUndirected(){

};

void GraphMatrix::addVertex(const std::string & data){

};

void GraphMatrix::addEdge(const double & data, const Vertex & u, const Vertex & v){

};

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