;Ejercicio 11

(deffacts hecho
	(dato 8)
	(dato 1)
	(dato 5)
	(dato verde)
	(dato 45)
	(todos-los-datos))

(defrule inserta
(dato ?x)
?v<-(todos-los-datos $?valores)

	;Comprobamos que no esta en todos los datos
	(not(todos-los-datos $? ?x $?))
=>
(retract ?v)
(assert(todos-los-datos $?valores ?x))
)