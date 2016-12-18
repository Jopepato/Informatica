"""
El script este es para usar las dos bases de datos de train y test
"""

import numpy as np
import matplotlib.pyplot as plt
import time
from sklearn.datasets import load_svmlight_file
from sklearn import svm
from sklearn.metrics import confusion_matrix

start_time = time.time()
#Cargamos la base de datos de train y test para spam
X_sparseTrain ,y_train = load_svmlight_file("train_spam.libsvm")
X_sparseTest, y_test = load_svmlight_file("test_spam.libsvm")

#Ahora convertimos a formato denso
X_train = np.array(X_sparseTrain.todense())
X_test = np.array(X_sparseTest.todense())

#Y ahora entrenamos el modelo para luego generalizar con el conjunto de test
svm_model = svm.SVC(kernel='linear',C=10**-1,gamma=200)
svm_model.fit(X_train, y_train)
y_predict = svm_model.predict(X_test)
matriz_confusion = confusion_matrix(y_test, y_predict)
#Imprimimos el CCR
#print "CCR: %f" % (svm_model.score(X_test, y_test)*100)
#print "Tiempo: %s" % (time.time() - start_time)
#print matriz_confusion

array = np.array([])
#Ahora vamos a recorrer ambos vectores y sacamos en los que se ha equivocado
for sample in range(0, y_test.size):
	if y_predict[sample] != y_test[sample]:
		array = np.append(array, sample+1)
		#np.append(array, X_sparseTest[sample][1])
		#print X_test[sample]
i=1
arrayPalabras = np.array([])
#print array
for j in array:
	for sample in X_test[int(j),:]:
		if int(sample) == 1:
			arrayPalabras = np.append(arrayPalabras, i)
		i= i+1
	i=1
arrayPalabras = np.unique(arrayPalabras)
#print arrayPalabras


#Ahora vamos a sacar las palabras del fichero
f = open('vocab.txt', 'r')
palabras = np.array([])
for line in f:
	line = line.strip('\n')
	strings = line.split('\t')
	palabras = np.append(palabras, strings[1])

#Ahora tenemos que imprimir las palabras que ya teniamos en arrayPalabras
string = ""
for indice in arrayPalabras:
	string = string + palabras[indice-1] + ", "

print string