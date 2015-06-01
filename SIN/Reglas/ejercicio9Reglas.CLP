;Ejercicio9
(deffacts hecho
	(dato 8)
	(dato 1)
	(dato 5)
	(dato verde)
	(dato 45)
	(todos-los-datos))

(defrule insertaOrden
?d<-(dato ?x)
?v<-(todos-los-datos $?valores)
=>
(retract ?d)
(retract ?v)
(assert(todos-los-datos $?valores ?x))
)