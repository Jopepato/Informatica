#include "algoritmos.hpp"
#include "ClaseTiempo.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h>
using namespace std;

int main(int argc, char ** argv){
/*
  if(argc!=5){
    cout << "Numero de parametros introducidos incorrecto" << endl;
    return(0);
  }
*/
  //Declaramos las variables que nos han introducido por linea de comandos
  int minEle;
  int maxEle;
  int incremento;
  int repeticion;
  uint64_t tiempo;
  vector<int> v;
  vector <int> tiempoMedio;
  vector <int> muestra;
  double media=0;
  int contador;
  Clock reloj;

  //Declaramos la semilla de la aleatoriedad
  srand(time(NULL));
  cout << "Introduce el numero minimo de elementos: ";
  cin >> minEle;
  cout << "Introduce el numero maximo de elementos: ";
  cin >> maxEle;
  cout << "Introduce el incremento en cada iteracion: ";
  cin >> incremento;
  cout << "Introduce el numero de veces: ";
  cin >> repeticion;

  //Ahora tenemos que coger los tiempos para mostrarlos despues

  for(int i = minEle; i<= maxEle; i+=incremento){

    for(int j=0; j<repeticion; j++){
      rellenaVector(v, i);
      //Aqui cogemos el tiempo y mostramos el tiempo por pantalla
      reloj.start();
      ordenacionBurbuja(v);
      reloj.stop();
      tiempo = reloj.elapsed();
      //cout << "Han pasado " << tiempo << " microsegundos" << endl;
      media = media + tiempo;
    }
    media = media/repeticion;
    tiempoMedio.push_back(media);
    muestra.push_back(i);

  }

muestraVector(tiempoMedio);
muestraVector(muestra);

}
