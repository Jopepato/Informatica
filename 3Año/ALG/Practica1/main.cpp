#include "algoritmos.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


int main(int argc, char ** argv){

  if(argc!=5){
    cout << "Numero de parametros introducidos incorrecto" << endl;
    return(0);
  }
  //Declaramos las variables que nos han introducido por linea de comandos
  int minEle = atoi(argv[1]);
  int maxEle = atoi(argv[2]);
  int incremento = atoi(argv[3]);
  int repeticion = atoi(argv[4]);
  vector<int> v;

  //Declaramos la semilla de la aleatoriedad
  srand(time(NULL));

  cout << "Probando la creacion" << endl;

  rellenaVector(v, maxEle);
  estaOrdenado(v);
  cout << "Mostramos el vector" << endl;

  muestraVector(v);

  ordenacionBurbuja(v);

  cout << "Ahora el vector ordenador" << endl;

  muestraVector(v);

}
