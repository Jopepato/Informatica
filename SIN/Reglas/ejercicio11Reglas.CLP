;Ejercicio 11

(deffacts hecho
	(dato 8)
	(dato 1)
	(dato 5)
	(dato verde)
	(dato 45)
	(todos-datos))

(defrule insertaOrden
(dato ?x)
?v<-(todos-datos $?valores)

	;Comprobamos que no esta en todos los datos
	(not(todos-datos $? ?x $?))
=>
(retract ?v)
(assert(todos-datos $?valores ?x))
)