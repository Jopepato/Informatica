//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica2.cpp
// Author      : Pedro A. Gutiérrez
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

    while((c = getopt(argc, argv, "t:T:i:l:h:e:m:bof:s")) != -1){

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
                //Comprobamos que es 0 o 1
                if(fvalue != 0 || fvalue != 1){
                    ayuda();
                    exit();
                }
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
	// Eta
	mlp.dEta = eta;
	// Mu
	mlp.dMu = mu;

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
		mlp.ejecutarAlgoritmo(pDatosTrain,pDatosTest,iteraciones,&(erroresTrain[i]),&(errores[i]),&(ccrsTrain[i]),&(ccrs[i]),fvalue);
		cout << "Finalizamos => CCR de test final: " << ccrs[i] << endl;
    }

    // Calcular media y desviación típica de los errores de Train y de Test
    // ....

    cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

	cout << "RESUMEN FINAL" << endl;
	cout << "*************" << endl;
    cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
    cout << "Error de test (Media +- DT): " << mediaError << " +- " << desviacionTipicaError << endl;
    cout << "CCR de entrenamiento (Media +- DT): " << mediaCCRTrain << " +- " << desviacionTipicaCCRTrain << endl;
    cout << "CCR de test (Media +- DT): " << mediaCCR << " +- " << desviacionTipicaCCR << endl;
	return EXIT_SUCCESS;
}

