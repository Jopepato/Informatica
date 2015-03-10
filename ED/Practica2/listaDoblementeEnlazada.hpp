#ifndef LISTADOBLEMENTEENLAZADA_H_
#define LISTADOBLEMENTEENLAZADA_H_

#include "listaOrdenada.hpp"
#include "nodo.hpp"


class listaDoblementeEnlazada : public listaOrdenada {

    private:


    public:

              //Observadores
              inline bool esUltimo(int pos){
                assert(esValida(pos));
                
                for(int i = 0; i<pos; i++){

                }

              };
              inline bool esValida(int pos){
                int contador = 0;
                struct nodo * aux = head_;
                while(aux != NULL){
                  contador++;
                  aux = aux_->sig;
                }

                if(pos == contador)
                  return true;
                else
                  return false;

              };


};









#endif
