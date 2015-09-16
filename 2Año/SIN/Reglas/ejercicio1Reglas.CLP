;Ejercicio 1 de reglas


(deffacts granja
	(sonido kikiriki)
	(sonido miau)
	(sonido guau)
	(sonido cuack)
	(sonido muuu)
	(sonido bee)
)


(defrule gallo
	(sonido kikiriki)
	=>
	(printout t "Se trata de un gallo" crlf)
)

(defrule gato
	(sonido miau)
	=>
	(printout t "Se trata de un gato" crlf)
)

(defrule perro
	(sonido guau)
	=>
	(printout t "Se trata de un perro" crlf)
)

(defrule pato
	(sonido cuack)
	=>
	(printout t "Se trata de un pato" crlf)
)

(defrule vaca
	(sonido muuu)
	=>
	(printout t "Se trata de un vaca" crlf)
)

(defrule oveja
	(sonido bee)
	=>
	(printout t "Se trata de un oveja" crlf)
)