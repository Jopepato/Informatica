#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>


//Estructura con todos los datos estadisticos que vamos a calcular
struct estadisticos{

	estadisticos ()
    : menor(0.0), //Valores por defecto de los argumentos opcionales.
    	mayor(0.0),
    	media(0.0),
    	varianza(0.0),
    	suma(0.0),
    	sumaCuadrados(0.0),
    	areaPos(0.0),
    	areaNeg(0.0),
    	numCeros(0.0),
    	numPos(0.0),
    	numNeg(0.0),
    	asimetria(0.0)
    	{}

	double menor;	//Menor valor
	double mayor;	//Mayor valor
	double media;
	double varianza;
	double suma;	//Suma de todos los valores
	double sumaCuadrados;	//Suma del cuadrado de todos los valores
	double areaPos;		//Suma de los valores positivos de la imagen
	double areaNeg;		//Suma de los valores negativos de la imagen
	double numCeros;	//Numero de ceros del canal
	double numPos;		//Numero de numeros positivos del canal
	double numNeg;		//Numero de numeros negativos del canal
	double asimetria;
};

void calculaEstadisticos(const cv::Mat &matriz,const cv::Mat &mascara);
void muestraEstadisticos(const struct estadisticos &est);
void help();


#endif