/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2016
 *********************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>

#include "PerceptronMulticapa.h"

using namespace imc;
using namespace std;

// ------------------------------
// Obtener un número real aleatorio en el intervalo [Low,High]
double realAleatorio(double Low, double High)
{
	double f = (double)rand() / RAND_MAX;
    return Low + f * (High - Low);
}

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa()
{


}

// Reservar memoria para las estructuras de datos
// nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
// Rellenar vector Capa* pCapas
int PerceptronMulticapa::inicializar(int nl, int npl[]) {

	pCapas = (Capa *)malloc(nl*sizeof(Capa));

	//Ahora rellenamos el pCapas
	for(int i=0; i<nl; i++){
		pCapas[i].nNumNeuronas = npl[i];
		pCapas[i].pNeuronas = (Neurona *)malloc(npl[i]*sizeof(Neurona));
	}
	
	return 1;
}


// ------------------------------
// DESTRUCTOR: liberar memoria
PerceptronMulticapa::~PerceptronMulticapa() {
	liberarMemoria();
}


// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria() {

		//jeeeeeeeeeeeeeeeeeee

		for(int i=0; i< nNumCapas; i++){
			//Vamos liberando todo dentro de cada capa
			for(int j=0; j<pCapas[i].nNumNeuronas; j++){
				free(pCapas[i].pNeuronas[j].w);
				free(pCapas[i].pNeuronas[j].deltaW);
				free(pCapas[i].pNeuronas[j].ultimoDeltaW);
				free(pCapas[i].pNeuronas[j].wCopia);
			}
			free(pCapas[i].pNeuronas);
		}

		free(pCapas);

}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios() {

	//Asignamos los pesos aleatorios a las neuronas, dichos pesos son el numero de neuronas de la capa anterior
	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			//Reservamos memoria para el vector de pesos de cada neurona
			pCapas[i].pNeuronas[j].w = (double *)malloc(pCapas[i-1].nNumNeuronas*sizeof(double));

			for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
				//Asignamos el numero aleatorio al vector de entradas de dicha neurona
				pCapas[i].pNeuronas[j].w[k] = realAleatorio(-1, 1);
			}

		}
	}

}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input) {

	for(int i=0; i<pCapas[0].nNumNeuronas; i++){
		pCapas[0].pNeuronas[i].x = input[i];
	}
}

// ------------------------------
// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
void PerceptronMulticapa::recogerSalidas(double* output) {

	//Guardamos las x de la ultima capa en el output
	for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
		output[i] = pCapas[nNumCapas-1].pNeuronas[i].x; 
	}

}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos() {

	//Asignamos los pesos aleatorios a las neuronas, dichos pesos son el numero de neuronas de la capa anterior
	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			//Reservamos memoria para el vector de pesos de cada neurona
			pCapas[i].pNeuronas[j].wCopia = (double *)malloc(pCapas[i-1].nNumNeuronas*sizeof(double));

			for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
				//Salvamos los pesos en copiaW
				pCapas[i].pNeuronas[j].wCopia[k] = pCapas[i].pNeuronas[j].w[k];
			}

		}
	}

}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos() {

	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
				//Restauramos los pesos de copiaW
				pCapas[i].pNeuronas[j].w[k] = pCapas[i].pNeuronas[j].wCopia[k];
			}

		}
	}

}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
void PerceptronMulticapa::propagarEntradas() {

	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){



		}
	}

}

// ------------------------------
// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
double PerceptronMulticapa::calcularErrorSalida(double* target) {
	double mse = 0.0;

	//Recorremos las neuronas de salida y comparamos con el target
	for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
		mse += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
	}

	//Dividimos entre el numero de neuronas de la ultima capa
	mse = mse/pCapas[nNumCapas-1].nNumNeuronas;

	return mse;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
void PerceptronMulticapa::retropropagarError(double* objetivo) {

}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {

}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos() {

}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed() {

	//Vamos a imprimir la red
	cout << "Vamos  a imprimir las entradas de las neuronas" << endl << endl;

		for(int i=1; i<nNumCapas; i++){
			cout << "Capa: " << i << endl;
			for(int j=0; j<pCapas[i].nNumNeuronas; j++){
				for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
					//Restauramos los pesos de copiaW
					cout << pCapas[i].pNeuronas[j].w[k] << " ";
				}
				cout << endl;

			}
	}

}

// ------------------------------
// Simular la red: propagar las entradas hacia delante, computar el error, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
void PerceptronMulticapa::simularRedOnline(double* entrada, double* objetivo) {

}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {
	//Comprobamos que los ficheros existen
	ifstream myfile;
	Datos *aux = NULL;
	string line;
	myfile.open(archivo);
	if(myfile.is_open()){

		//Leemos el fichero y rellenamos Datos
		getline(myfile, line, ' ');
		aux->nNumEntradas = atoi(line.c_str());
		getline(myfile, line, ' ');
		aux->nNumSalidas = atoi(line.c_str());
		getline(myfile, line, '\n');
		aux->nNumPatrones = atoi(line.c_str());
		//Reservamos memoria para las matrices
		aux->entradas = (double **)malloc(aux->nNumPatrones * sizeof(double *));
		aux->salidas = (double **)malloc(aux->nNumPatrones * sizeof(double *));

		for(int i=0 ; i<aux->nNumPatrones; i++){
			aux->entradas[i] = (double *)malloc(aux->nNumEntradas*sizeof(double));
		}

		for(int i=0; i<aux->nNumPatrones; i++){
			aux->salidas[i] = (double *)malloc(aux->nNumSalidas*sizeof(double));
		}

		//Recorremos las filas metiendo los elemento en la matriz

		for(int i=0; i<aux->nNumPatrones; i++){

			for(int j=0; j<aux->nNumEntradas; j++){
				getline(myfile, line, ' ');
				aux->entradas[i][j] = atof(line.c_str());
			}

			for(int j=0; j<aux->nNumSalidas; j++){
				if(j != aux->nNumSalidas-1){
					getline(myfile, line, ' ');
					aux->salidas[i][j] = atof(line.c_str());
				}else{
					getline(myfile, line, '\n');
					aux->salidas[i][j] = atof(line.c_str());
				}
			}


		}

		return(aux);
	}else{
		cout << "El fichero no existe" << endl;
		exit(-1);
	}
}

// ------------------------------
// Entrenar la red on-line para un determinado fichero de datos
void PerceptronMulticapa::entrenarOnline(Datos* pDatosTrain) {
	int i;
	for(i=0; i<pDatosTrain->nNumPatrones; i++)
		simularRedOnline(pDatosTrain->entradas[i], pDatosTrain->salidas[i]);
}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
double PerceptronMulticapa::test(Datos* pDatosTest) {
	int i;
	double dAvgTestError = 0;
	for(i=0; i<pDatosTest->nNumPatrones; i++){
		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		dAvgTestError += calcularErrorSalida(pDatosTest->salidas[i]);
	}
	dAvgTestError /= pDatosTest->nNumPatrones;
	return dAvgTestError;
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmoOnline(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;
	double testError = 0;

	// Aprendizaje del algoritmo
	do {

		entrenarOnline(pDatosTrain);
		double trainError = test(pDatosTrain);
		// El 0.00001 es un valor de tolerancia, podría parametrizarse
		if(countTrain==0 || fabs(trainError - minTrainError) > 0.00001){
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}
		else{
			numSinMejorar++;
		}

		if(numSinMejorar==50){
			restaurarPesos();
			countTrain = maxiter;
		}

		countTrain++;

		cout << "Iteración " << countTrain << "\t Error de entrenamiento: " << trainError << endl;

	} while ( countTrain<maxiter );

	cout << "PESOS DE LA RED" << endl;
	cout << "===============" << endl;
	imprimirRed();

	cout << "Salida Esperada Vs Salida Obtenida (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		double* prediccion = new double[pDatosTest->nNumSalidas];

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);
		for(int j=0; j<pDatosTest->nNumSalidas; j++)
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j];
		cout << endl;
		delete[] prediccion;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}
