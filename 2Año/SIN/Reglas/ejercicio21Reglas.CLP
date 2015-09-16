;Ejercicio que calcula la mediana
;Tenemos que usar length para coger el tamaño del multicampo y asi ver cual es la mediana :>

(deffacts hechos
	(vector 2 4 5 6 4 2 1 3 4 6 4 3 2)
	(vector 2 3 4 5 4 3)
	(vector 2 3 45 3 1)
	(vector 3 5 3 1)
)


(defrule medianaimpar
	?h<-(vector $?cabeza ?x $?cola)
	(test (eq (length$ $?cabeza) (length$ $?cola)))
	=>
	(printout t "El vector " ?h " es impar y su numero del medio es " ?x crlf)
)

;Ahora la medianaPar

(defrule medianapar
	?h<-(vector $?cabeza ?x ?y $?cola)
	(test (eq (length$ $?cabeza) (length$ $?cola)))
	=>
	(printout t "El vector " ?h " es par y su mediana es " (/ (+ ?x ?y) 2) crlf)
)