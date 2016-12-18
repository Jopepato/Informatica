"""
El script este es para usar las dos bases de datos de train y test
"""

import numpy as np
import matplotlib.pyplot as plt

from sklearn.datasets import load_svmlight_file
from sklearn import svm
from sklearn.cross_validation import StratifiedShuffleSplit

# Cargar el dataset
X_sparse, y = load_svmlight_file("dataset3.libsvm")

# Convertirlo a formato denso
X = np.array(X_sparse.todense())

#Ahora estratificamos
sss = StratifiedShuffleSplit(y, test_size=0.2, train_size=0.8)

for train_index, test_index in sss:
	X_train, X_test = X[train_index], X[test_index]
	y_train, y_test = y[train_index], y[test_index]

#Ahora entrenamos con el conjunto de train y sacamos el score con el de test
svm_model = svm.SVC(kernel='rbf',C=2,gamma=200)
svm_model.fit(X_train, y_train)

score = svm_model.score(X_test, y_test)*100

print "El ccr obtenido es: %f" % (score)