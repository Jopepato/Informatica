#ifndef LISTAORDENADA_H_
#define LISTAORDENADA_H_

#include <cassert>
#include <nodo.hpp>

using namespace std;

//Esta hay que hacerla virtual


namespace ed{


template <class T>


template <class T>
class ListaOrdenada{

    private:
      struct nodo* nodos_;
      T* head_;


    public:
        inline ListaOrdenadaDoblementeEnlazada(int maximo){
          nodos_ = (struct nodo*)malloc(maximo*sizeof(struct nodo));
          head_ = nodos_; //Apunta al primer elemento
        };

        //Observadores









        //Constructores


  };




}








#endif
