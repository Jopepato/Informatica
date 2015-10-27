;Ejercicio 6

(deffacts hechos
	(hecho 2 3 5 56 7 6 3 4)
	(hecho 1 2 3 5 4)
	(hecho 4 6 3 2 2)
	(hecho 4 2 2 3)
)

(defrule encuentra3y4
	(hecho $?cabeza ?x $?medio ?y $?cola)
	
	(or
		(and 
		(test(eq ?x 3))
		(test(eq ?y 4))
		)
		(and
		(test(eq ?y 3))
		(test(eq ?x 4))
		)
	)

	(test(= (mod(length$ $?medio) 2) 1))
	=>
	(printout t "El hecho " $?cabeza crlf)

)