;Ejercicio 12


(deffacts hechos
	(dato 4)
	(dato 5)
	(dato 2)
	(dato 5)
	(dato 10)
)


(defrule imprimeOrdenado
	?d<-(dato ?x)
	(not (dato ?y&:(< ?y ?x)))
	=>
	(retract ?d)
	(printout t ?x crlf)
)