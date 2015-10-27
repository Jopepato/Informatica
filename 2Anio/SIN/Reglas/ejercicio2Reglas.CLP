(deftemplate animal
	(slot nombre)
	(slot sonido)
)


(deffacts granja
	(animal (nombre gato) (sonido miau))
	(animal (nombre perro) (sonido guau))
	(animal (nombre gallo) (sonido kikiriki))
	(animal (nombre vaca) (sonido muu))
	(animal (nombre oveja) (sonido bee))
	(animal (nombre pato) (sonido cuack))
)

(defrule sonido

	(animal (nombre ?x) (sonido ?y))
	=>
	(printout t "El/la " ?x " hace " ?y crlf)
)