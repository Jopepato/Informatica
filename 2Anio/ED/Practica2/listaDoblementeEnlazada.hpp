#ifndef LISTADOBLEMENTEENLAZADA_H_
#define LISTADOBLEMENTEENLAZADA_H_

#include "listaOrdenada.hpp"
#include "nodo.hpp"


class listaDoblementeEnlazada : public listaOrdenada {

    private:
              doubleLinkedNode * nodo;

    public:

              //Aqui se hacen las funciones unicas e imprescindibles para la lista

              //Observadores
              //Aqui miramos si el item es el ultimo
              inline bool esUltimo(const int &pos){
                int contador = 0;
                struct nodo * aux = head_;
                assert(esValida(pos));
                while(aux != NULL){
                  contador++;
                  aux = aux_->sig;
                }

                if(pos == contador)
                  return true;
                else
                  return false;
              };
              inline bool esValida(const int &pos){
                struct nodo * aux = head_;
                bool esVerdad = true;
                  for(int i=0; i<pos; i++){
                    if(aux != NULL){
                      aux = aux->sig;
                      esVerdad =true;
                    }else{
                      esVerdad = false;
                    }
                  }
                return(esVerdad);
              };

              inline T item(const int &pos){
                assert(esValida(pos));
                struct nodo * aux =head_;
                //Una vex comprobado que esa posicion es valida pues devolvemos el elemento de esa posicion
                for(int i=0; i<pos; i++){
                  aux = aux->sig;
                }
                return(aux);
              };

              inline int buscaItem(const T &item,const int &from){
                struct nodo * aux = head_;
                //Comprobamos que el from es una posicion valida
                int contador=0;
                int posicion;
                bool encontrado = false;

                while(aux != null){
                  if(aux.item == item){
                    posicion = contador;
                    encontrado = true;
                  }
                  contador++;
                }
                //Esto es que no lo hemos encontrado
                //Por lo tanto devolvemos -1
                if(!encontrado){
                  return (-1);
                }
                //Devolvemos la posicion del item a partir del from :>
                return(posicion - from);
              };



              //Modificadores

              inline void inserta(const T &item){
              //Lo malo de esto es que la lista la tiene que estar ordenada
              //Por lo tanto el insertar esta complicao :<


              



              };


              inline void borraPosicion(const int &pos){



              };


};









#endif
