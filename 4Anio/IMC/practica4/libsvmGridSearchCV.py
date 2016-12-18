"""
En este script vamos a obtener los mejores valores para C y Gamma
"""

import numpy as np
import matplotlib.pyplot as plt
import time
from sklearn.datasets import load_svmlight_file
from sklearn import svm
from sklearn.cross_validation import StratifiedShuffleSplit
from sklearn.grid_search import GridSearchCV


start_time = time.time()
svm_model = svm.SVC(kernel='rbf',C=2,gamma=200)

# Cargar el dataset
X_sparse, y_train = load_svmlight_file("train_digits.libsvm")
# Convertirlo a formato denso
X_train = np.array(X_sparse.todense())

X_sparse, y_test = load_svmlight_file("test_digits.libsvm")
X_test = np.array(X_sparse.todense())


Cs = np.logspace(-5, 15, num=11, base=2)
Gs = np.logspace(-15, 3, num=9, base=2)
svm_model = svm.SVC()
optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs, gamma = Gs),n_jobs=-1, cv=10)
optimo.fit(X_train, y_train)

print "CCR: %f" % (optimo.score(X_test, y_test)*100)
print optimo.best_params_
print "%s seconds" % (time.time()-start_time)