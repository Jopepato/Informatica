;Ejercicio 5
;Que elimine todas las apariciones de 1

(deffacts hechos
	(hecho a 3 4 2 4 5 3 1 3 4 1 3 5 2 1)
)

(defrule eliminaUno
	?h<-(hecho $?cola ?x $?cabeza)
	(test (eq ?x 1))
	=>
	(retract ?h)
	(assert (hecho $?cola $?cabeza))

)