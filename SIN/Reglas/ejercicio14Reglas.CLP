;Ejercicio del factorial


(deffacts factoriales
	(factorial 3)
	(factorial 4)
	(factorial 2)
	(factorial 5)
)

(defrule mostrarAux	
	?h<-(aux ?x ?y ?z)
	(test(eq ?x 0))

	=>
	(retract ?h)
	(printout t "El factorial de " ?z " es: " ?y crlf)

)

(defrule copiaFactorial
	?h<-(factorial ?x)
	=>
	(assert (aux ?x 1 ?x))
)


(defrule factorial

	?h<-(aux ?x ?y ?z)
	(test(> ?x 0))
	=>
	(retract ?h)
	(assert (aux (- ?x 1) (* ?y ?x) ?z))
)
