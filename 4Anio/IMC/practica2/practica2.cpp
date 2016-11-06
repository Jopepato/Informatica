//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica2.cpp
// Author      : José Pérez-Parras Toledano
// Version     : 2016
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para cojer la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <math.h>
#include <fstream>
#include "PerceptronMulticapa.h"
#include "practica2.hpp"

using namespace imc;
using namespace std;

int main(int argc, char **argv) {


    bool tflag = false, Tflag= false, bflag = false, oflag = false, sflag = false;
    char *tvalue = NULL , *Tvalue = NULL;
    int ivalue = 1000, lvalue = 1, hvalue = 5, fvalue = 0;
    float evalue = 0.1, mvalue = 0.9;
    fstream myfile;
    int c;
    // Procesar la línea de comandos

    // Leer iteraciones, capas y neuronas desde la línea de comandos

    // Leer sesgo, eta y mu de la línea desde comandos

    // Leer fichero de train y de test desde la línea de comandos

    // Leer tipo de error (0 MSE, 1 Entropía cruzada) de la línea de comandos

    while((c = getopt(argc, argv, "bost:T:i:l:h:e:m:f:")) != -1){

        switch(c){

            case 't':
                tflag= true;
                tvalue = optarg;
                break;

            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;

            //Controlar lo que mete el usuario
            case 'i':
                ivalue = atoi(optarg);
                break;

            case 'l':
                lvalue = atoi(optarg);
                break;

            case 'h':
                hvalue = atoi(optarg);
                break;

            case 'e':
                evalue = atof(optarg);
                break;

            case 'm':
                mvalue = atof(optarg);
                break;

            case 'b':
                bflag = true;
                break;
            case 'o':
                oflag = true;
                break;
            case 'f':
                fvalue = atoi(optarg);
                break;
            case 's':
                sflag = true;
                break;
            case '?':
                ayuda();
            default:
                break;
        }

    }

    if(!tflag || !Tflag){
        cout << "El programa no se puede ejecutar sin los ficheros de entrenamiento y test" << endl;
        ayuda();
        return(-1);
    }

	PerceptronMulticapa mlp;

	Datos * pDatosTrain = mlp.leerDatos(tvalue);
	Datos * pDatosTest = mlp.leerDatos(Tvalue);

    // Inicializar el vector "topología"
    // (número de neuronas por cada capa, incluyendo la de entrada
    //  y la de salida)
    // ...

    int * topologia;
    topologia = (int*)malloc((lvalue+2)*sizeof(int));
    topologia[0] = pDatosTest->nNumEntradas;
    //Y lo rellenamos
    for(int i=1; i<lvalue+1; i++){
            topologia[i] = hvalue;
    }
    topologia[lvalue+1] = pDatosTest->nNumSalidas;

	// Sesgo
	mlp.bSesgo = bflag;
	// Online?
	mlp.bOnline = oflag;
    
    evalue = evalue/pDatosTrain->nNumPatrones;
	// Eta
	mlp.dEta = evalue;
	// Mu
	mlp.dMu = mvalue;

    // Inicialización propiamente dicha
	mlp.inicializar(lvalue+2,topologia, sflag);
    //En la inicialización ya le hemos metido a cada capa si va a ser de tipo sigmoide o softmax


    // Semilla de los números aleatorios
    int semillas[] = {10,20,30,40,50};
    double *errores = new double[5];
    double *erroresTrain = new double[5];
    double *ccrs = new double[5];
    double *ccrsTrain = new double[5];
    for(int i=0; i<5; i++){
    	cout << "**********" << endl;
    	cout << "SEMILLA " << semillas[i] << endl;
    	cout << "**********" << endl;
		srand(semillas[i]);
		mlp.ejecutarAlgoritmo(pDatosTrain,pDatosTest,ivalue,&(erroresTrain[i]),&(errores[i]),&(ccrsTrain[i]),&(ccrs[i]),fvalue);
		cout << "Finalizamos => CCR de test final: " << ccrs[i] << endl;
    }
    
    double mediaErrorTrain = 0.0, mediaErrorTest=0.0, desviacionTipicaErrorTrain=0.0, desviacionTipicaErrorTest=0.0;
    double mediaCCRTrain = 0.0, mediaCCR = 0.0, desviacionTipicaCCRTrain = 0.0, desviacionTipicaCCR = 0.0;


    //Las calculamos
    for(int i=0; i<5; i++){
        mediaErrorTrain += erroresTrain[i];
        mediaErrorTest += errores[i];
        mediaCCRTrain += ccrsTrain[i];
        mediaCCR += ccrs[i];
    }
    mediaErrorTest /= 5;
    mediaErrorTrain /= 5;
    mediaCCRTrain /= 5;
    mediaCCR /= 5;

    //Ahora la desviacion tipica
    double auxTest = 0.0, auxTrain=0.0;
    double auxCCRTest = 0.0, auxCCRTrain = 0.0;

    for(int i=0; i<5; i++){
        auxTest += pow(errores[i] - mediaErrorTest,2);
        auxTrain += pow(erroresTrain[i] - mediaErrorTrain, 2);
        auxCCRTrain += pow(ccrsTrain[i] - mediaCCRTrain, 2);
        auxCCRTest += pow(ccrs[i] - mediaCCR, 2);
    }
    desviacionTipicaErrorTest = sqrt(0.25*auxTest);
    desviacionTipicaErrorTrain = sqrt(0.25*auxTrain);
    desviacionTipicaCCRTrain = sqrt(0.25*auxCCRTrain);
    desviacionTipicaCCR = sqrt(0.25*auxCCRTest);

    cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

	cout << "RESUMEN FINAL" << endl;
	cout << "*************" << endl;
    cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
    cout << "Error de test (Media +- DT): " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
    cout << "CCR de entrenamiento (Media +- DT): " << mediaCCRTrain << " +- " << desviacionTipicaCCRTrain << endl;
    cout << "CCR de test (Media +- DT): " << mediaCCR << " +- " << desviacionTipicaCCR << endl;
	return EXIT_SUCCESS;
}

