;Ejercicio 6 de Reglas

(deffacts hechos
	(vector vector1 1 4 5 2 3 6 54 7 6 6 4)
	(vector vector2 3 5 6 4)
	(vector vector3 4 5 6 7 3)
)


(defrule compruebaNumerosEntre3Y4
	(vector ?nombre
	 $?cabeza
	 ?x&:(numberp ?x)
	 $?valores
	 ?y&:(numberp ?y)
	 $?cola)
	
	(test (or
		(and(= ?x 3)(= ?y 4))
		(and(= ?x 4)(= ?y 3))
		)
	)
	

	(test(= (mod (length$ $?valores) 2) 1))
	=>
	(printout t "El " ?nombre " cumple esta condicion" crlf)
	
)