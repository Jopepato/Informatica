;Hacer 22
(deffacts hechos
	(vector v1 2 3 4 5 6 7 8 3 1 3 4)
	(vector v2 1 2 3 4 5 4 3 2 1)
	(vector v3 9 8 7 6 5 6 7 8 9)
)


(defrule copiaVector
	(vector ?nombre $?valores)
=>
	(assert (aux ?nombre $?valores))
)

(defrule acorta
	?a<-(aux ?nombre ?x&:(numberp ?x) $?valores ?y&:(numberp ?y))
	(aux ?nombre $?medio)
	(test (= ?x ?y))
	(test(> (length$ $?medio) 1))
=>
	(retract ?a)
	(assert(aux ?nombre $?valores))
)


(defrule esSimetrico
	(aux ?nombre $?valores)
	(test (< (length$ $?valores) 2))
	=>
	(printout t "El vector " ?nombre " es simetrico" crlf)
)