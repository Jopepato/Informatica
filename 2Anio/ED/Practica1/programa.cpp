/**
\file programa.cpp
\brief Programa principal para usar las funciones y los TADs "Recta2D" y "Punto2D"
\author José Pérez-Parras Toledano
\date 1 de Marzo de 2015
*/


/**
  \mainpage Practica 1 y uso de TADs "Recta2D" y "Punto2D"
  \author José Pérez-Parras Toledano
  \date 1 de Marzo de 2015
*/

//Incluimos los ficheros de cabecera
#include "Punto2D.hpp"
#include "Recta2D.hpp"
#include "funciones.hpp"
#include <string>
#include <vector>
#include <iostream>

/**
  \main Programa principal
  \brief Realiza las llamadas a las funciones para cargar los contornos y calcular el error
*/


int main(){

  vector<int> aproximacion;
  vector< Punto2D< double> > contorno;
  string ficheroContorno, ficheroAproximacion;

  double error;


  cout << "Introduce el nombre del fichero con el contorno: ";
  cin >> ficheroContorno;
  cout << "Introduce el nombre del fichero con la aproximacion: ";
  cin >> ficheroAproximacion;

  //Cargamos el vector con la figura primigenia
  cargarContorno(contorno, ficheroContorno.c_str());

  //Cargamos el otro vector con la aproximacion
  cargarAproximacionPoligonal(aproximacion, ficheroAproximacion.c_str());


  error = calcularError(contorno, aproximacion);

  cout << "El error cometido es: " << error << endl;




  return 0;
}
