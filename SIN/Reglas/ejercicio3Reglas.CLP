(deffacts hechos
	(datos 2 4)
	(datos 5 4)
	(datos 2 9)
	(datos 1 10)
	(datos 10 1)
)


(defrule compruebaMayor
	(datos ?x&:(numberp ?x) ?y&:(numberp ?y))
	(test(< ?x ?y))
	=>
	(printout t ?x " " ?y crlf)
)