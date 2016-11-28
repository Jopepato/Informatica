#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 12:37:04 2016

@author: José Pérez-Parras Toledano
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import random

from scipy.spatial import distance
from sklearn.cluster import KMeans
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import mean_squared_error

def entrenar_rbf(fichero_train, fichero_test, num_rbf, clasificacion, eta, l2):
    """ Función principal
        Recibe los siguientes parámetros:
            - fichero_train: nombre del fichero de entrenamiento.
            - fichero_test: nombre del fichero de test.
            - num_rbf: número de neuronas de tipo RBF.
            - clasificacion: True si el problema es de clasificacion.
            - eta: valor del parámetro de regularización para la Regresión 
              Logística.
            - l2: True si queremos utilizar L2 para la Regresión Logística. 
              False si queremos usar L1.
        Devuelve:
            - train_mse: Error de tipo Mean Squared Error en entrenamiento. 
              En el caso de clasificación, calcularemos el MSE de las 
              probabilidades predichas frente a las objetivo.
            - test_mse: Error de tipo Mean Squared Error en test. 
              En el caso de clasificación, calcularemos el MSE de las 
              probabilidades predichas frente a las objetivo.
            - train_ccr: Error de clasificación en entrenamiento. 
              En el caso de regresión, devolvemos un cero.
            - test_ccr: Error de clasificación en test. 
              En el caso de regresión, devolvemos un cero.
    """
    train_inputs, train_outputs, test_inputs, test_outputs = lectura_datos(fichero_train, 
                                                                           fichero_test)

    kmedias, distancias, centros = clustering(clasificacion, train_inputs, 
                                              train_outputs, num_rbf)
    
    radios = calcular_radios(centros, num_rbf)
    
    matriz_r = calcular_matriz_r(distancias, radios)

    if not clasificacion:
        coeficientes = invertir_matriz_regresion(matriz_r, train_outputs)
    else:
        logreg = logreg_clasificacion(matriz_r, train_outputs, eta, l2)


    distancias_test = calcular_distancias(test_inputs, centros, num_rbf)
    matriz_r_test = calcular_matriz_r(distancias_test, radios)
    
    if not clasificacion:
        
        #Tenemos que mirar el error del MSE de los train y test para después sacarlo
        #Multiplicaremos r de test por los coeficientes y así obtendremos la y estimada esto debemos hacerlo tanto para test como para train
        matriz_y_estimada_train = np.dot(matriz_r, coeficientes)
        matriz_y_estimada_test = np.dot(matriz_r_test, coeficientes)
        train_mse = mean_squared_error(train_outputs, matriz_y_estimada_train)
        test_mse = mean_squared_error(test_outputs, matriz_y_estimada_test)
        train_ccr = 0
        test_ccr = 0
    else:
        """
        Obtener las predicciones de entrenamiento y de test y calcular
              el CCR. Calcular también el MSE, comparando las probabilidades 
              obtenidas y las probabilidades objetivo
        """
        #Tenemos que mirar el error de MSE de train y test, también hemos de mirar el CCR que serán el % de los patrones bien clasificados
        train_ccr = logreg.score(matriz_r, train_outputs)*100
        test_ccr = logreg.score(matriz_r_test, test_outputs)*100
        
        train_predict = logreg.predict(matriz_r)
        test_predict = logreg.predict(matriz_r_test)
        train_mse = mean_squared_error(train_predict, train_outputs)
        test_mse = mean_squared_error(test_predict, test_outputs)        
        
    return train_mse, test_mse, train_ccr, test_ccr
    
def lectura_datos(fichero_train, fichero_test):
    """ Realiza la lectura de datos.
        Recibe los siguientes parámetros:
            - fichero_train: nombre del fichero de entrenamiento.
            - fichero_test: nombre del fichero de test.
        Devuelve:
            - train_inputs: matriz con las variables de entrada de 
              entrenamiento.
            - train_outputs: matriz con las variables de salida de 
              entrenamiento.
            - test_inputs: matriz con las variables de entrada de 
              test.
            - test_outputs: matriz con las variables de salida de 
              test.
    """

    train = pd.read_csv(fichero_train, header = None)
    test = pd.read_csv(fichero_test, header = None)
    #Ahora sacamos las variables de entrada y las variables de salida de cada una
    train_inputs = train.values[:, 0:-1]
    train_outputs = train.values[:, -1]
    test_inputs = test.values[:, 0:-1]
    test_outputs = test.values[:, -1]

    return train_inputs, train_outputs, test_inputs, test_outputs

def inicializar_centroides_clas(train_inputs, train_outputs, num_rbf):
    """ Inicializa los centroides para el caso de clasificación.
        Debe elegir, aprox., num_rbf/num_clases patrones por cada clase.
        Recibe los siguientes parámetros:
            - train_inputs: matriz con las variables de entrada de 
              entrenamiento.
            - train_outputs: matriz con las variables de salida de 
              entrenamiento.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - centroides: matriz con todos los centroides iniciales
                          (num_rbf x num_entradas).
    """
    #Aqui vamos a hacer lo de los centroides
    #Primero comprobamos cuantos patrones hay de cada clase
    
    num_clases = np.unique(train_outputs).shape[0]
    num_entradas = train_inputs.shape[1]
    centroides = np.empty([num_rbf, num_entradas])
    clases = np.empty([num_rbf])
    for i in range(num_rbf):
        j = i % num_clases
        clases[i] = np.unique(train_outputs)[j]
    
    for i in range(num_rbf):
        #Metemos 'num_rbf' patrones en la matriz centroides
        while 1:
            rand = random.randint(0, train_outputs.shape[0]-1)
            if train_outputs[rand] == clases[i]:
                centroides[i] = train_inputs[rand]
                np.delete(train_inputs, [rand])
                np.delete(train_outputs, [rand])
                break   
    
    return centroides

def clustering(clasificacion, train_inputs, train_outputs, num_rbf):
    """ Realiza el proceso de clustering. En el caso de la clasificación, se
        deben escoger los centroides usando inicializar_centroides_clas()
        En el caso de la regresión, se escogen aleatoriamente.
        Recibe los siguientes parámetros:
            - clasificacion: True si el problema es de clasificacion.
            - train_inputs: matriz con las variables de entrada de 
              entrenamiento.
            - train_outputs: matriz con las variables de salida de 
              entrenamiento.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - kmedias: objeto de tipo sklearn.cluster.KMeans ya entrenado.
            - distancias: matriz (num_patrones x num_rbf) con la distancia 
              desde cada patrón hasta cada rbf.
            - centros: matriz (num_rbf x num_entradas) con los centroides 
              obtenidos tras el proceso de clustering.
    """
    
    if clasificacion == True:
        centros = inicializar_centroides_clas(train_inputs, train_outputs, num_rbf)
        kmedias = KMeans(n_clusters = num_rbf, init = centros, n_init=1, max_iter = 500)
    else:
        #Obtenemos num_brf numeros aleatorios
        kmedias = KMeans(n_clusters = num_rbf, init = 'random', max_iter = 500)
        
    
    kmedias.fit(train_inputs, train_outputs)
 
    centros = kmedias.cluster_centers_

    #Ahora vamos a calcular las distancias de cada patron a su cluster mas cercano
    distancias = calcular_distancias(train_inputs, centros, num_rbf)      
    return kmedias, distancias, centros

def calcular_distancias(inputs, centros, num_rbf):
    
    distancias = np.empty([inputs.shape[0], num_rbf])
    for i in range(0, inputs.shape[0]):
        for j in range(0, centros.shape[0]):
            #Calculamos la distancia euclidea de cada patron para cada rbf
            distancias[i,j] = distance.euclidean(inputs[i,:], centros[j,:])
    #Con eso ya tendriamos una matriz con la distancia a cada centroide de cada uno de los patrones
    return distancias


def calcular_radios(centros, num_rbf):
    """ Calcula el valor de los radios tras el clustering.
        Recibe los siguientes parámetros:
            - centros: conjunto de centroides.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - radios: vector (num_rbf) con el radio de cada RBF.
    """
    #Este lo hace bien

    radios = np.empty(num_rbf)
    aux = 0.0
    #Para cada elemento de los radios calculamos el radio que será el sumatorio 
    for i in range(0, num_rbf):
        for j in range(0, num_rbf):
            if i!=j:
                aux += distance.euclidean(centros[i], centros[j])
        radios[i] = aux/(2*num_rbf-1)
        aux = 0.0
    
        
    return radios

def calcular_matriz_r(distancias, radios):
    """ Devuelve el valor de activación de cada neurona para cada patrón 
        (matriz R en la presentación)
        Recibe los siguientes parámetros:
            - distancias: matriz (num_patrones x num_rbf) con la distancia 
              desde cada patrón hasta cada rbf.
            - radios: array (num_rbf) con el radio de cada RBF.
        Devuelve:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al principio, en la primera columna, un vector con todos los 
              valores a 1, que actuará como sesgo.
    """
    
    matriz_r = np.empty([distancias.shape[0], distancias.shape[1]+1])
    matriz_r[:, 0] = 1
    
    #Vamos mirando cada distancia con el radio y asi vamos viendo
    #Si la distancia es mayor que el radio entonces la salida de la neurona es 0
    #Mientras que si la distancia es menor que el radio, la salida será 1
    for i in range(0, matriz_r.shape[0]):
        for j in range(0, matriz_r.shape[1]-1):
            matriz_r[i][j+1] = math.exp(-(distancias[i][j]**2)/(2*radios[j]**2))
    
    return matriz_r

def invertir_matriz_regresion(matriz_r, train_outputs):
    """ Devuelve el vector de coeficientes obtenidos para el caso de la 
        regresión (matriz beta en las diapositivas)
        Recibe los siguientes parámetros:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al principio, en la primera columna, un vector con todos los 
              valores a 1, que actuará como sesgo.
            - train_outputs: matriz con las variables de salida de 
              entrenamiento.
        Devuelve:
            - coeficientes: vector (num_rbf+1) con el valor del sesgo y del 
              coeficiente de salida para cada rbf.
    """

    #Haremos el caso mas comun que será lo de tener que hacer la matriz de Moore-Penrose
    moore = np.linalg.pinv(matriz_r)
    
    coeficientes = np.dot(moore,train_outputs) #Esta operacion lo que nos da es la transpuesta
    
    return coeficientes

def logreg_clasificacion(matriz_r, train_outputs, eta, l2):
    """ Devuelve el objeto de tipo regresión logística obtenido a partir de la
        matriz R.
        Recibe los siguientes parámetros:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al principio, en la primera columna, un vector con todos los 
              valores a 1, que actuará como sesgo.
            - train_outputs: matriz con las variables de salida de 
              entrenamiento.
            - eta: valor del parámetro de regularización para la Regresión 
              Logística.
            - l2: True si queremos utilizar L2 para la Regresión Logística. 
              False si queremos usar L1.
        Devuelve:
            - logreg: objeto de tipo sklearn.linear_model.LogisticRegression ya
              entrenado.
    """

    pen = ''
    if l2 == True:
        pen = 'l2'
    else:
        pen = 'l1'
        
    logreg = LogisticRegression(penalty=pen,C = 1/eta, fit_intercept = False)
    #En esta habria que pasarle R o los train_inputs, pero claro eso no lo tenemos
    logreg.fit(matriz_r, train_outputs)

    return logreg

if __name__ == "__main__":
    train_mses = np.empty(5)
    train_ccrs = np.empty(5)
    test_mses = np.empty(5)
    test_ccrs = np.empty(5)
    
    for s in range(10,60,10):
        print "-----------"
        print "Semilla: %d" % s
        print "-----------"
        
        np.random.seed(s)
        train_mses[s/10-1], test_mses[s/10-1], train_ccrs[s/10-1], test_ccrs[s/10-1] = \
            entrenar_rbf(fichero_train='./csv/train_digits.csv', 
                         fichero_test='./csv/test_digits.csv', num_rbf=10, clasificacion=True, eta=0.0001, l2=True)
        print "MSE de entrenamiento: %f" % train_mses[s/10-1]
        print "MSE de test: %f" % test_mses[s/10-1]
        print "CCR de entrenamiento: %.2f%%" % train_ccrs[s/10-1]
        print "CCR de test: %.2f%%" % test_ccrs[s/10-1]
    
    """
    Imprimir la media y la desviación típica del MSE y del CCR
    """
    mediaErrorTrain = np.mean(train_mses)
    mediaErrorTest = np.mean(test_mses)
    mediaErrorCCRTrain = np.mean(train_ccrs)
    mediaErrorCCRTest = np.mean(test_ccrs)
    
    #Ahora hacemos la desviacion tipica
    desvErrorTrain = np.std(train_mses)
    desvErrorTest = np.std(test_mses)
    desvCCRTrain = np.std(train_ccrs)
    desvCCRTest = np.std(test_ccrs)

    #Aqui imprimimos los errores de mse y ccr finales de media y desviacion tipica      
    print "HEMOS TERMINADO TODAS LAS SEMILLAS"
    print "----------------------------------"
    print "RESUMEN FINAL"
    print "*************"
    print "Error de entrenamiento (Media  +- desv): %f +- %f" % (mediaErrorTrain, desvErrorTrain)
    print "Error de test (Media  +- desv): %f +- %f" % (mediaErrorTest, desvErrorTest)
    print "CCR de entrenamiento (Media  +- desv): %f%% +- %f%%" % (mediaErrorCCRTrain, desvCCRTrain)
    print "CCR de test (Media  +- desv): %f%% +- %f%%" % (mediaErrorCCRTest, desvCCRTest)