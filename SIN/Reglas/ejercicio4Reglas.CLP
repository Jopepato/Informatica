(deffacts hechos
	(datos 2 4 53 5 3 6 4 5 6 3 4 343  5 3)
	(datos 4 2 4 5 3 2 2 1 1 1)
	(datos 1 2 4 6 4 6 8 6 65 4 100)
	(datos 2 2 5 6 7 8 9 4 2 99)
)

(defrule compruebaParYMenor
	(datos ?x&:(numberp ?x) $?a ?y&:(numberp ?y))
	(test(<= ?x ?y))
	(test(= (mod ?x 2) 0))
	=>
	(printout t "Cumple la condicion: "?x " " $?a " " ?y crlf)
)