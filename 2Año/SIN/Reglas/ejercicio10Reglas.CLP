;Ejercicio 10
;Ordenar un vector

(deffacts hechos
	(vector v1 2 4 2 5 6 7 3 5)
	(vector v2 2 4 5 6 8 7)
)

(defrule ordenaVector
	?h<-(vector ?nombre $?cabeza ?x ?y $?cola)
	(test (< ?y ?x))
	=>
	(retract ?h)
	(assert (vector ?nombre $?cabeza ?y ?x $?cola))
)