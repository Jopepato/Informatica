;Ejercicio 12 de la relacion :>

(deffacts ejer12
	(dato 4)
	(dato 3)
	(dato 60)
	(dato 2)
	(dato 99)
)

(defrule insertaOrden
?d<-(dato ?x&:(numberp ?x))
(not (dato ?y&:(< ?y ?x)))
=>
(retract ?d)
(printout t "Variable datos: " ?x crlf)
)