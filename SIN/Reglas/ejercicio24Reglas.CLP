;El 22 pero sin quitar los hechos ni redefinirlos

(deffacts hechos
	(vector v1 2 3 4 5 6 7 8 3 1 3 4)
	(vector v2 1 2 3 4 5 4 3 2 1)
	(vector v3 9 8 7 6 5 6 7 8 9)
)


(defrule esSimetrico
	(vector ?nombre $?valores)
	(forall	(vector ?nombre $?cabeza ?x $?medio ?y $?cola&:(eq(length$ $?cabeza)(length$ $?cola)))
		(test (= ?x ?y))
	)
	=>
	(printout t "El vector " ?nombre " es simetrico" crlf)
)