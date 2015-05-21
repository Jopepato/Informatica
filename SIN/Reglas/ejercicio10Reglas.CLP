;Ejercicio 10

(deffacts hechos
	(vector v1 5 6 4 2 1)
	(vector v2 1 2 6 7 8)
	(vector v3 9 8 4 5 2 5 7 6)
)

(defrule ordenaVector 
?h<-(vector ?nombre
	$?cabeza
	?x&:(numberp ?x)
	?y&:(< ?y ?x)
	$?cola)
=>
(retract ?h)
;Cuando esta desordenado cambiamos el orden para que se inserte en orden
(assert (vector ?nombre $?cabeza ?y ?x $?cola))
)