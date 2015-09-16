;Ejercicio 13

(deffacts hecho
	(dato 8)
	(dato 1)
	(dato 5)
	(dato verde)
	(dato 45)
	(todos-los-datos))

(defrule ordenaOrden
	(dato ?x&:(numberp ?x))
	?v<-(todos-los-datos $?valores)
	(forall 
	 (dato ?y&:(numberp ?y)&:(< ?y ?x))
 	 (todos-los-datos $? ?y $?)
	)
	(not (todos-los-datos $? ?x $?))
=>
(retract ?v)
(assert(todos-los-datos $?valores ?x))
)

