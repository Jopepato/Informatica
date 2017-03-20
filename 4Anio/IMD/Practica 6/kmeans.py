"""
El script este es para usar las dos bases de datos de train y test
"""

import numpy as np
import matplotlib.pyplot as plt

from sklearn.datasets import load_svmlight_file
from sklearn import svm
from sklearn.model_selection import KFold
from sklearn.cluster import KMeans
from sklearn.metrics import mean_squared_error
from sklearn.metrics import confusion_matrix
from scipy.spatial import distance

# Cargar el dataset
X_sparse, y = load_svmlight_file("ionosphere.libsvm")

# Convertirlo a formato denso
X = np.array(X_sparse.todense())

#Ahora estratificamos
kf = KFold(n_splits=10, shuffle=True)

for train_index, test_index in kf.split(y):
	X_train, X_test = X[train_index], X[test_index]
	y_train, y_test = y[train_index], y[test_index]

kmeans = KMeans(init='random', n_clusters=2).fit(X_train)

prediccion = kmeans.predict(X_test)

print "SSE: ", mean_squared_error(y_test, prediccion)
test_ccr = np.sum(prediccion == y_test) * (prediccion.shape[0]**-1)*100
print confusion_matrix(y_test, prediccion)
print test_ccr


#Ahora hay que hacer la matriz de distancias
matrizDistancias = np.empty([X_test.shape[0], X_test.shape[0]])
for i in range(0, X_test.shape[0]):
	for j in range(0, X_test.shape[0]):
		matrizDistancias[i,j] = distance.euclidean(X_test[i,:], X_test[j,:])


print matrizDistancias

#Falta la matriz de incidencia

matrizIncidencia = np.empty([X_test.shape[0], X_test.shape[0]])
for i in range(0, X_test.shape[0]):
	for j in range(0, X_test.shape[0]):
		if prediccion[i] == prediccion[j]:
			matrizIncidencia[i,j] = 1
		else:
			matrizIncidencia[i,j] = 0

print matrizIncidencia