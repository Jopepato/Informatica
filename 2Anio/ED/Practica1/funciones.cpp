/**
\file funciones.cpp
\brief Desarrollo de las funciones para el error y la carga de ficheros
\author José Pérez-Parras Toledano
\date 1 de Marzo de 2015
*/

#include "funciones.hpp"

/**
  \fn cargarContorno(vector<Punto2D<double> > &contorno,const char *ficheroContorno)
  \brief Carga un vector de puntos con los puntos almacenados en un fichero
  \param contorno Referencia a un vector de Punto2D del tipo double
  \param ficheroContorno Referencia constante de un vector de caracteres que almacena el nombre del fichero
  \pre El fichero debe existir
  \post El vector debe estar cargado con los puntos del fichero
  \return void
*/

void cargarContorno(vector<Punto2D<double> > &contorno,const char *ficheroContorno){


  assert( contorno.empty());

  fstream fichero;
  contorno.clear();
  double x, y;

  fichero.open(ficheroContorno, ios::in);

  while(fichero>>x>>y){
    Punto2D<double> aux(x, y);
    contorno.push_back(aux);
  }

  assert(!contorno.empty());

  //Cerramos el fichero
  fichero.close();

}

/**
  \fn cargarAproximacionPoligonal (vector<int> &aproximacionPoligonal,const char *ficheroAproximacionPoligonal)
  \brief Carga un vecto de enteros con el numero de puntos del fichero de aproximacion
  \param aproximacionPoligonal Referencia de un vector de enteros que almacenara dichos puntos
  \param ficheroAproximacionPoligonal Referencia constante a un vector de caracteres que almacena el nombre del fichero con la aproximación
  \pre El fichero debe existir
  \post El vector debe estar cargado con los puntos del fichero
  \return void
*/
void cargarAproximacionPoligonal (vector<int> &aproximacionPoligonal,const char *ficheroAproximacionPoligonal){

  fstream fichero;
  assert(aproximacionPoligonal.empty());
  aproximacionPoligonal.clear();
  fichero.open(ficheroAproximacionPoligonal, ios::in);

  int x;
  while(fichero>>x){

    aproximacionPoligonal.push_back(x);
  }

  fichero.close();

  assert(!aproximacionPoligonal.empty());
}

/**
  \fn calcularError(const vector< Punto2D<T> > &contorno, const vector<int> &aproximacionPoligonal)
  \brief Calcula el error entre la aproximación y la figura original
  \param contorno Referencia constante al vector de Punto2D de tipo double que almacena los puntos de la figura original
  \param aproximacionPoligonal Referencia constante al vector de enteros que tiene almacenada la aproximacion
  \pre Ambos vectores deben de tener los puntos a comparar
  \post Ninguna
  \return error De tipo T que almacena el error cometido entre la figura original y la aproximacion
*/

double calcularError(const vector< Punto2D<double> > &contorno, const vector<int> &aproximacionPoligonal){


  //Comprobamos que los vectores no estan vacios
  assert (!contorno.empty());
  assert (!aproximacionPoligonal.empty());



  int TAM = aproximacionPoligonal.size();
  int p1, p2;
  double error=0;


  for( int i = 0 ; i < TAM -1  ; i++ ){
    if(i < (TAM-2)){
      //Mientras que no se llegue al ultimo lo hacemos normal
      p1 = aproximacionPoligonal[i];
      p2 = aproximacionPoligonal[i+1];

    }else{ //Cuando llegamos al final tenemos que coger la recta con el primero
      p1 = aproximacionPoligonal[i];
      p2 = aproximacionPoligonal[0];

    }

    //Declaramos los puntos y la recta que vamos a usar para calcular el error
    Punto2D <double> punto1 = contorno[p1];
    Punto2D <double> punto2 = contorno[p2];

    Recta2D <double> recta (punto1, punto2); //Hacemos la recta con los puntos obtenidos

    Punto2D <double> punto (0.0, 0.0); //Declaramos un punto que será el que usems para saber el error



    if(i < (TAM-2)){
      for(int j=p1+1 ; j<p2; j++){
        punto = contorno[j];//Cargamos el punto con el punto del contorno real
        error = error + pow(recta.Distancia(punto), 2);
      }
    }else{ //Cuando es el ultimo tenemos que dividir en dos for
      //Este for desde ese punto final hasta el final del contorno
      for(int j=p1+1; j<contorno.size()-1; j++){
        punto = contorno[j];
        error = error + pow(recta.Distancia(punto), 2);

      }
      //Y este for desde el principio hasta el segundo punto de la recta
      for(int j=0; j<p2; j++){
        punto = contorno[j];
        error = error + pow(recta.Distancia(punto), 2);

      }

    }
  }

  return (error);
}
