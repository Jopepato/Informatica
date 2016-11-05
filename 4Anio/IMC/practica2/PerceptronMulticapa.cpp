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
// Obtener un número entero aleatorio en el intervalo [Low,High]
int enteroAleatorio(int Low, int High) {
	int random = rand()%(High-Low + 1) + Low;
	return random;
}

// ------------------------------
// Obtener un número real aleatorio en el intervalo [Low,High]
double realAleatorio(double Low, double High) {
	double f = (double)rand() / RAND_MAX;
    return Low + f * (High - Low);
}

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa() {
	dEta = 0.1;
	dMu = 0.9;
	bSesgo = false;
	pCapas = NULL;
	nNumCapas = 3;
	bOnline = false;
}

// ------------------------------
// Reservar memoria para las estructuras de datos
// nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
// Rellenar vector Capa* pCapas
int PerceptronMulticapa::inicializar(int nl, int npl[],bool bSigmoideCapaSalida) {

	//pCapas = (Capa *)malloc(nl*sizeof(Capa));
	nNumCapas = nl;
	int aux = 0;
	pCapas = (Capa *)malloc(nl*sizeof(Capa));
	//Ahora rellenamos el pCapas
	pCapas[0].nNumNeuronas = npl[0];
	pCapas[0].pNeuronas = (Neurona *)malloc(npl[0]*sizeof(Neurona));


	for(int i=1; i<nl; i++){
		pCapas[i].nNumNeuronas = npl[i];
		pCapas[i].pNeuronas = (Neurona *)malloc(npl[i]*sizeof(Neurona));
		pCapas[i].tipo = 0;
			for(int j=0; j<npl[i]; j++){
				aux = npl[i-1] + 1;
				pCapas[i].pNeuronas[j].w = (double *)malloc(aux*sizeof(double));
				pCapas[i].pNeuronas[j].deltaW = (double *)malloc(aux*sizeof(double));
				pCapas[i].pNeuronas[j].ultimoDeltaW = (double *)malloc(aux*sizeof(double));
				pCapas[i].pNeuronas[j].wCopia = (double *)malloc(aux*sizeof(double));

				for(int k=0; k<aux; k++){
					pCapas[i].pNeuronas[j].w[k] = 0.0;
					pCapas[i].pNeuronas[j].deltaW[k] = 0.0;
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = 0.0;
					pCapas[i].pNeuronas[j].wCopia[k] = 0.0;
				}
			}
			aux = 0;
	}
	if(bSigmoideCapaSalida){
		pCapas[nNumCapas-1].tipo = 1;
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
		
	for(int i=0; i<nNumCapas; i++){
		//Vamos liberando todo dentro de cada capa
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			if(i!=0){
				free(pCapas[i].pNeuronas[j].w);
				free(pCapas[i].pNeuronas[j].deltaW);
				free(pCapas[i].pNeuronas[j].ultimoDeltaW);
				free(pCapas[i].pNeuronas[j].wCopia);
			}
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
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++){
				//Asignamos el numero aleatorio al vector de entradas de dicha neurona
				double x = realAleatorio(-1.0, 1.0);
				pCapas[i].pNeuronas[j].w[k] = x;
				pCapas[i].pNeuronas[j].wCopia[k] = x;
			}
		}
	}

}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input) {

	for(int i=0; i<pCapas[0].nNumNeuronas; i++){
		pCapas[0].pNeuronas[i].x = input[i];
		pCapas[0].pNeuronas[i].dX = input[i];
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
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++){
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
			for(int k=0; k<pCapas[i-1].nNumNeuronas+1; k++){
				//Restauramos los pesos de copiaW
				pCapas[i].pNeuronas[j].w[k] = pCapas[i].pNeuronas[j].wCopia[k];
			}

		}
	}

}

// ------------------------------
// Calcular y propagar las salidas de las neuronas, desde la segunda capa hasta la última
//En la ultima capa miramos si la capa es softmax y actuamos de forma distinta
void PerceptronMulticapa::propagarEntradas() {

//Hay que cambiar esta funcion para la ultima capa
double aux = 0.0;
double sumatorioNet = 0.0;
double net = 0.0;
	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++){
					aux += pCapas[i].pNeuronas[j].w[k] * pCapas[i-1].pNeuronas[k-1].x;
			}
			if(bSesgo){
				aux += pCapas[i].pNeuronas[j].w[0];
			}
			pCapas[i].pNeuronas[j].x = (1/(1 + exp((-1)*aux)));
			aux = 0.0;
		}
	}

	//Voy a hacer otro bucle para ver si la ultima capa es softmax
	if(pCapas[nNumCapas-1].tipo == 1){
		//Tenemos softmax en la ultima capa
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			for(int j=1; j<pCapas[nNumCapas-2].nNumNeuronas; j++){
				net += pCapas[nNumCapas-1].pNeuronas[i].w[j] * pCapas[nNumCapas-2].pNeuronas[j-1].x;
			}
			if(bSesgo){
				net += pCapas[nNumCapas-1].pNeuronas[i].w[0];
			}
			sumatorioNet += exp(net);
			net = 0.0;
		}
		//Una vez tenemos el sumatorio completo podemos sacar los outs de las salidas de la ultima capa
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			for(int j=1; j<pCapas[nNumCapas-2].nNumNeuronas; j++){
				net += pCapas[nNumCapas-1].pNeuronas[i].w[j] * pCapas[nNumCapas-2].pNeuronas[j-1].x;
			}
			if(bSesgo){
				net += pCapas[nNumCapas-1].pNeuronas[i].w[0];
			}
			pCapas[nNumCapas-1].pNeuronas[i].x = exp(net)/exp(sumatorioNet);
			net = 0.0;
		}

		//Una vez hecho esto ya tendremos bien las salidas		
	}
}

// ------------------------------
// Calcular el error de salida del out de la capa de salida con respecto a un vector objetivo y devolverlo
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::calcularErrorSalida(double* target, int funcionError) {

	double error = 0.0;
	//Aqui se podrá calcular de dos formas, una ya la tenemos de la practica anterior
	if(funcionError == 0){
		//El error que se calcula es el de mse
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			error += pow(target[i] - pCapas[nNumCapas-1].pNeuronas[i].x, 2);
		}
		error = error/pCapas[nNumCapas-1].nNumNeuronas;
	}else{
		//Se calcula el error por entropiacruzada
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			error += target[i] * log(pCapas[nNumCapas-1].pNeuronas[i].x);
		}
	}

	return error;
}


// ------------------------------
// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::retropropagarError(double* objetivo, int funcionError) {

	double sumatorio2=0.0;
	//Solo tenemos que cambiar las derivadas para la capa de salida que es la de tipo softmax
	//Además también se mirará la función de error a considerar.
	if(pCapas[nNumCapas-1].tipo == 0){
		for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
			if(funcionError == 0){
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i] - pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}else{
				pCapas[nNumCapas-1].pNeuronas[i].dX =  (-1)*(objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
			}
		}
	}else{
		//Ahora para la capa de salida con softmax es distinto
		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++){
			for(int i=0; i<pCapas[nNumCapas-1].nNumNeuronas; i++){
				if(i==j){
					if(funcionError == 0){
						sumatorio2 += (objetivo[i]-pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}else{
						sumatorio2 += (objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (1 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
				}else{
					if(funcionError == 0){
						sumatorio2 += (objetivo[i]-pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}else{
						sumatorio2 += (objetivo[i]/pCapas[nNumCapas-1].pNeuronas[i].x) * pCapas[nNumCapas-1].pNeuronas[i].x * (0 - pCapas[nNumCapas-1].pNeuronas[i].x);
					}
				}
			}
			pCapas[nNumCapas-1].pNeuronas[j].dX = (-1)*sumatorio2;
			sumatorio2 = 0.0;
		}
	}

	//Esto tiene pinta de estar bien

	double sumatorio = 0.0;

	//Y ahora para las otras capas
	for(int i=nNumCapas-2; i>=0; i--){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			//Calculamos el sumatorio de las entradas y la derivada de la capa siguiente
			for(int k=0; k<pCapas[i+1].nNumNeuronas; k++){
				sumatorio += pCapas[i+1].pNeuronas[k].w[j] * pCapas[i+1].pNeuronas[k].dX;
			}

			pCapas[i].pNeuronas[j].dX = sumatorio * pCapas[i].pNeuronas[j].x * (1 -pCapas[i].pNeuronas[j].x);
		}
	}

}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio() {

	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){
			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++){
				pCapas[i].pNeuronas[j].deltaW[k] +=  pCapas[i].pNeuronas[j].dX * pCapas[i-1].pNeuronas[k-1].x;
			}

			if(bSesgo){
				pCapas[i].pNeuronas[j].deltaW[0] += pCapas[i].pNeuronas[j].dX;
			}
		}
	}

}

// ------------------------------
// Actualizar los pesos de la red, desde la segunda capa hasta la última
void PerceptronMulticapa::ajustarPesos() {

	for(int i=1; i<nNumCapas; i++){
		for(int j=0; j<pCapas[i].nNumNeuronas; j++){

			for(int k=1; k<pCapas[i-1].nNumNeuronas+1; k++){
				pCapas[i].pNeuronas[j].w[k] += (-1)*dEta * pCapas[i].pNeuronas[j].deltaW[k] - dMu * (dEta*pCapas[i].pNeuronas[j].ultimoDeltaW[k]);
			}

			if(bSesgo){
				pCapas[i].pNeuronas[j].w[0] += (-1)*dEta * pCapas[i].pNeuronas[j].deltaW[0] - dMu * (dEta*pCapas[i].pNeuronas[j].ultimoDeltaW[0]);
			}
		}
	}

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
					cout << pCapas[i].pNeuronas[j].w[k] << " ";
				}
				cout << "Salida: " << pCapas[i].pNeuronas[j].x;
				cout << endl;

			}
	}

}

// ------------------------------
// Simular la red: propagar las entradas hacia delante, retropropagar el error y ajustar los pesos
// entrada es el vector de entradas del patrón y objetivo es el vector de salidas deseadas del patrón
// El paso de ajustar pesos solo deberá hacerse si el algoritmo es on-line
// Si no lo es, el ajuste de pesos hay que hacerlo en la función "entrenar"
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::simularRed(double* entrada, double* objetivo, int funcionError) {

	if(bOnline){
		//Lo del deltaW no sé como es, ah si se pone todo a cero
		for(int i=1; i<nNumCapas; i++){
			for(int j=0; j<pCapas[i].nNumNeuronas; j++){
				for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
					pCapas[i].pNeuronas[j].deltaW[k] = 0.0;
				}
			}
		}
		alimentarEntradas(entrada);
		propagarEntradas();
		retropropagarError(objetivo, funcionError);
		acumularCambio();
		ajustarPesos();

	}else{
		alimentarEntradas(entrada);
		propagarEntradas();
		retropropagarError(objetivo, funcionError);
		acumularCambio();
	}

}

// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {
	//Comprobamos que los ficheros existen
	ifstream myfile;
	Datos *aux = new Datos;
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
		myfile.close();
		return(aux);
	}else{
		cout << "El fichero no existe" << endl;
		exit(-1);
	}
}


// ------------------------------
// Entrenar la red para un determinado fichero de datos (pasar una vez por todos los patrones)
// Si es offline, después de pasar por ellos hay que ajustar pesos. Sino, ya se ha ajustado en cada patrón
void PerceptronMulticapa::entrenar(Datos* pDatosTrain, int funcionError) {
	//En esta función llamamos a la funcion de simularRed
	
	if(!bOnline){
		for(int i=1; i<nNumCapas; i++){
			for(int j=0; j<pCapas[i].nNumNeuronas; j++){
				for(int k=0; k<pCapas[i-1].nNumNeuronas; k++){
					pCapas[i].pNeuronas[j].ultimoDeltaW[k] = pCapas[i].pNeuronas[j].deltaW[k];
					pCapas[i].pNeuronas[j].deltaW[k] = 0.0;
				}
			}
		}
	}
	for (int i=0; i<pDatosTrain->nNumPatrones; i++){
		simularRed(pDatosTrain->entradas[i], pDatosTrain->salidas[i], funcionError);
	}
	if(!bOnline){
		ajustarPesos();
	}

}

// ------------------------------
// Probar la red con un conjunto de datos y devolver el error MSE cometido
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
double PerceptronMulticapa::test(Datos* pDatosTest, int funcionError) {

	//Tenemos que probar para todos los patrones
	double dAvgTestError = 0;
	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		//Alimentamos entradas y propagamos para despues sacar el error
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		dAvgTestError += calcularErrorSalida(pDatosTest->salidas[i], funcionError);
	}
	//Despues de probar para todos los patrones, miramos la funcion error, porque cada una se divide por una cosa distinta
	if(funcionError == 1){
		dAvgTestError /= (-1)*pDatosTest->nNumPatrones * pCapas[nNumCapas-1].nNumNeuronas;
	}else{
		dAvgTestError /= pDatosTest->nNumPatrones;
	}

	return dAvgTestError;
}


// ------------------------------
// Probar la red con un conjunto de datos y devolver el error CCR cometido
double PerceptronMulticapa::testClassification(Datos* pDatosTest) {
	double ccr = 0.0;

	//Tenemos que mirar las salidas tanto de nuestra red neuronal como del test y quedarnos con la mas grande, si dicha neurona es la misma entonces aumentamos el ccr
	int indiceDatosTest = 0;
	int indiceNeuronas = 0;
	double maximoTest = 0.0, maximoNeuronas =0.0;

	for(int i=0; i<pDatosTest->nNumPatrones; i++){
		indiceNeuronas = 0;
		indiceDatosTest = 0;
		maximoTest = 0.0;
		maximoNeuronas = 0.0;
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();

		for(int j=0; j<pCapas[nNumCapas-1].nNumNeuronas; j++){

			//Nos vamos quedando con el mayor indice
			if(pCapas[nNumCapas-1].pNeuronas[j].x > maximoNeuronas){
				maximoNeuronas = pCapas[nNumCapas-1].pNeuronas[j].x;
				indiceNeuronas = j;
			}

			if(pDatosTest->salidas[i][j] > maximoTest){
				maximoTest = pDatosTest->salidas[i][j];
				indiceDatosTest = j;
			}
		}

		//Ahora comprobamos si son el mismo y actuamos en consecuencia
		if(indiceNeuronas == indiceDatosTest){
			ccr++;
		}
	}
	//Aplicamos al ccr el efecto porcentaje
	ccr = 100 * ccr/pDatosTest->nNumPatrones;

	return ccr;
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
void PerceptronMulticapa::ejecutarAlgoritmo(Datos * pDatosTrain, Datos * pDatosTest, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int funcionError)
{
	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	double minTrainError = 0;
	int numSinMejorar;

	// Aprendizaje del algoritmo
	do {

		entrenar(pDatosTrain,funcionError);
		double trainError = test(pDatosTrain,funcionError);
		if(countTrain==0 || fabs(trainError - minTrainError) > 0.00001){
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}
		else{
			numSinMejorar++;
		}

		if(numSinMejorar==50)
			countTrain = maxiter;

		countTrain++;
		cout << "Iteración " << countTrain << "\t Error de entrenamiento: " << trainError << endl;

	} while ( countTrain<maxiter );

	restaurarPesos();

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
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j] << " \\\\ " ;
		cout << endl;
		delete[] prediccion;

	}

	*errorTest=test(pDatosTest,funcionError);
	*errorTrain=minTrainError;
	*ccrTest = testClassification(pDatosTest);
	*ccrTrain = testClassification(pDatosTrain);

}

