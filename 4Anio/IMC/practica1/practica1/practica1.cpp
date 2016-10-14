//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : José Pérez-Parras Toledano
// Version     :
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
#include "imc/PerceptronMulticapa.h"
#include "practica1.hpp"

using namespace imc;
using namespace std;

int main(int argc, char **argv) {

    // Procesar la línea de comandos
    bool tflag = false, Tflag= false, bflag = false;;
    char *tvalue = NULL , *Tvalue = NULL;
    int ivalue = 1000, lvalue = 1, hvalue = 5;
    float evalue = 0.1, mvalue = 0.9;
    fstream myfile;
    int c;
    // ....

    //hvalue = topologia
    //Vamos a procesar la linea de comandos

    // Leer iteraciones, capas y neuronas desde la línea de comandos

    // Leer sesgo, eta y mu de la línea desde comandos

    // Leer fichero de train y de test desde la línea de comandos
    while((c = getopt(argc, argv, "t:T:i:l:h:e:m:b")) != -1){

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

            case '?':
                ayuda();
            default:
                break;
        }

    }

    //Comprueba si existen ficheros de entrenamiento y de test, si no existen dichos ficheros cierra el programa

    if(tflag == false || Tflag == false){
        //Nos salimos porque no hay ficheros de entrada
        ayuda();
        exit(-1);
    }

    PerceptronMulticapa mlp;

    Datos * pDatosTrain = mlp.leerDatos(tvalue);
    Datos * pDatosTest = mlp.leerDatos(Tvalue);

    // Inicializar el vector "topología"
    int * topologia;

    topologia = (int*)malloc((lvalue+2)*sizeof(int));
    topologia[0] = pDatosTest->nNumEntradas;
    //Y lo rellenamos
    for(int i=1; i<lvalue+1; i++){
            topologia[i] = hvalue;
    }
    topologia[lvalue+1] = pDatosTest->nNumSalidas;


    // (número de neuronas por cada capa, incluyendo la de entrada
    //  y la de salida)
    // ...

    // Sesgo
    mlp.bSesgo = bflag;

    // Eta
    mlp.dEta = evalue;

    // Mu
    mlp.dMu = mvalue;

    // Inicialización propiamente dicha
    mlp.inicializar(lvalue+2,topologia);


    // Semilla de los números aleatorios
    int semillas[] = {10,20,30,40,50};
    double *erroresTest = new double[5];
    double *erroresTrain = new double[5];
    for(int i=0; i<5; i++){
        srand(semillas[i]);
    	cout << "**********" << endl;
    	cout << "SEMILLA " << semillas[i] << endl;
    	cout << "**********" << endl;
        mlp.ejecutarAlgoritmoOnline(pDatosTrain,pDatosTest,ivalue,&(erroresTrain[i]),&(erroresTest[i]));
		cout << "Finalizamos => Error de test final: " << erroresTest[i] << endl;
    }

    cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;

    // Calcular media y desviación típica de los errores de Train y de Test
    // ....

    double mediaErrorTrain = 0.0, mediaErrorTest=0.0, desviacionTipicaErrorTrain=0.0, desviacionTipicaErrorTest=0.0;

    //Las calculamos
    for(int i=0; i<5; i++){
        mediaErrorTrain += erroresTrain[i];
        mediaErrorTest += erroresTest[i];
    }
    mediaErrorTest /= 5;
    mediaErrorTrain /= 5;

    //Ahora la desviacion tipica
    double auxTest = 0.0, auxTrain=0.0;

    for(int i=0; i<5; i++){
        auxTest += pow(erroresTest[i] - mediaErrorTest,2);
        auxTrain += pow(erroresTrain[i] - mediaErrorTrain, 2);
    }
    desviacionTipicaErrorTest = sqrt((1/4)*auxTest);
    desviacionTipicaErrorTrain = sqrt((1/4)*auxTrain);


    cout << "INFORME FINAL" << endl;
    cout << "*************" << endl;
    cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
    cout << "Error de test (Media +- DT):          " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
    return EXIT_SUCCESS;
}

