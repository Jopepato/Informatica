
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 10:14:36 2015

@author: jopepato
"""

import numpy as np
import matplotlib.pyplot as plt

from sklearn.datasets import load_svmlight_file
from sklearn import svm

# Cargar el dataset
X_sparse, y = load_svmlight_file("dataset2.libsvm")

# Convertirlo a formato denso
X = np.array(X_sparse.todense())

# Entrenar el modelo SVM
svm_model = svm.SVC(kernel='rbf',C=10**3,gamma=100)
svm_model.fit(X, y)

# Representar los puntos
plt.figure(1)
plt.clf()
plt.scatter(X[:, 0], X[:, 1], c=y, zorder=10, cmap=plt.cm.Paired)

# Representación gráfica de la SVM
# --------------------------------
plt.axis('tight')
# Extraer límites
x_min = X[:, 0].min()
x_max = X[:, 0].max()
y_min = X[:, 1].min()
y_max = X[:, 1].max()

# Crear un grid con todos los puntos y obtener el valor Z devuelto por la SVM
XX, YY = np.mgrid[x_min:x_max:500j, y_min:y_max:500j]
Z = svm_model.decision_function(np.c_[XX.ravel(), YY.ravel()])

# Hacer un plot a color con los resultados
Z = Z.reshape(XX.shape)
plt.pcolormesh(XX, YY, Z > 0, cmap=plt.cm.Paired)
plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], linestyles=['--', '-', '--'],
                levels=[-.5, 0, .5])

plt.show()
