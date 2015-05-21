;Ejercicio9
(deffacts hecho
	(dato 8)
	(dato 1)
	(dato 5)
	(dato verde)
	(dato 45)
	(todos-datos))

(defrule insertaOrden
?d<-(dato ?x)
?v<-(todos-datos $?valores)
=>
(retract ?d)
(retract ?v)
(assert(todos-datos $?valores ?x))
)