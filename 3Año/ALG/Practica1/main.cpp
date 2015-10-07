#include "algoritmos.hpp"
#include "ClaseTiempo.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h>
using namespace std;

int main(int argc, char ** argv){

  if(argc!=5){
    cout << "Numero de parametros introducidos incorrecto" << endl;
    return(0);
  }

  //Declaramos las variables que nos han introducido por linea de comandos
  int minEle;
  int maxEle;
  int incremento;
  int repeticion;
  double tiempoLineal, tiempoCuadratico;
  vector<double> v, x;
  vector <double> tiempoMedioLineal, tiempoMedioLinealEst;
  vector <double> tiempoMedioCuadratico, tiempoMedioCuadraticoEst;
  vector <double> muestra;
  double mediaLineal=0, mediaCuadratica=0;
  double a0Lineal, a1Lineal, a0Pol, a1Pol, a2Pol;
  double r2Lineal, r2Pol;
  Clock relojLineal, relojCuadratico;
  string nombreFichero;

  //Declaramos la semilla de la aleatoriedad
  srand(time(NULL));
  //Pasamos los argumentos a las variables
  minEle = atoi(argv[1]);
  maxEle = atoi(argv[2]);
  incremento = atoi(argv[3]);
  repeticion = atoi(argv[4]);

  //Ahora tenemos que coger los tiempos para mostrarlos despues

  for(int i = minEle; i<= maxEle; i+=incremento){

    for(int j=0; j<repeticion; j++){
      rellenaVector(v, i);
      rellenaVector(x, i);

      //Aqui cogemos el tiempo y mostramos el tiempo por pantalla
      //Cogemos el tiempo del lineal
      relojLineal.start();
      quickSortIterative(v, 0, v.size());
      relojLineal.stop();
      tiempoLineal = relojLineal.elapsed();

      //Cogemos el tiempo del cuadratico
      relojCuadratico.start();
      ordenacionBurbuja(v);
      relojCuadratico.stop();
      tiempoCuadratico = relojCuadratico.elapsed();

      //Aqui hacemos el sumatorio de los tiempos
      mediaLineal += tiempoLineal;
      mediaCuadratica += tiempoCuadratico;


    }


    mediaLineal = mediaLineal/repeticion;
    mediaCuadratica = mediaCuadratica/repeticion;
    tiempoMedioLineal.push_back(mediaLineal);
    tiempoMedioCuadratico.push_back(mediaCuadratica);
    muestra.push_back(i);

  }

  cout << "Vector de tiempos del algoritmo lineal: " << endl;
  muestraVector(tiempoMedioLineal);
  cout << "Vector de tiempos del algoritmo cuadratico: " << endl;
  muestraVector(tiempoMedioCuadratico);
  cout << "Vector de muestras: " << endl;
  muestraVector(muestra);

  calcularAjusteLineal(muestra, tiempoMedioLineal, a0Lineal, a1Lineal);
  calcularAjustePolinomico(muestra, tiempoMedioCuadratico, a0Pol, a1Pol, a2Pol);

  cout << "Lineal: " << endl;
  cout << "a0: " << a0Lineal << "\n" << "a1: " << a1Lineal << endl;
  cout << "Cuadratico: " << endl;
  cout << "a0: " << a0Pol << "\n" << "a1: " << a1Pol << "\n" << "a2: " << a2Pol << endl;

  //Llamamos a las otras funciones para terminar
  calcularTiemposEstimadosLineales(muestra, tiempoMedioLineal, a0Lineal, a1Lineal,tiempoMedioLinealEst, r2Lineal);
  calcularTiemposEstimadosCuadraticos(muestra, tiempoMedioCuadratico, a0Pol, a1Pol, a2Pol, tiempoMedioCuadraticoEst, r2Pol);

  //Mostamos las cosas por pantalla

  cout << "Tiempos estimados del algoritmo lineal: " << endl;
  muestraVector(tiempoMedioLinealEst);
  cout << "Tiempos estimados del algoritmo polinomico: " << endl;
  muestraVector(tiempoMedioCuadraticoEst);

  cout << "Ecuacion Lineal: " << endl;
  cout << a0Lineal << " + " << a1Lineal << "*n*log(n)" << endl;
  cout << "Coeficiente de determinacion lineal: " << r2Lineal << endl;
  cout << "Ecuacion cuadratica: " << endl;
  cout << a0Pol << " + " << a1Pol << "*n + " << a2Pol << "*n^2" << endl;
  cout << "Coeficiente de determinacion cuadratico: " << r2Pol << endl;

  cout << "Introduce el nombre del fichero donde se almacenaran los datos: ";
  cin >> nombreFichero;


  guardarTiempos(muestra, tiempoMedioCuadratico, tiempoMedioCuadraticoEst, tiempoMedioLineal, tiempoMedioLinealEst, nombreFichero);

  cout << "Fichero creado" << endl;


  //Ahora le pediremos numeros al usuario hasta que ponga un 0 para salirnos
  int n;
  while(1){
    cout << "Introduce el numero de elementos para calcular el tiempo aproximado (0 para salir): ";
    cin >> n;

    if(n!=0){
      calculaTiempoEnDias(n, a0Lineal, a1Lineal, a0Pol, a1Pol, a2Pol);
    }else{
      return 0;
    }


  }
    
  return 0;

}
