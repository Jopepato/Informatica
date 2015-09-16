;Ejercicio8

(deffacts hechos
	(vector v1 1 3 4 5)
	(vector v2 3 4 2)
	(vector v3 2 3 4 3)
)

(defrule vectorNoOrdenado
 (vector ?nombre $?cabeza ?x ?y $?cola)
 (test (> ?x ?y)) 
=>
 (printout t "El vector " ?nombre " no esta ordenado" crlf)
)