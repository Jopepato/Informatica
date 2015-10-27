;Ejercicio 7 de la relacion de reglas

(deffacts datos
	(datos 1 2 4 5 67 a vn wjokdas 2 kjfds 47 9903479834 hksdfukhdfs)
	(datos a a a a a a a a a a a 2)
	(datos b e 4 2 5 a f 5 3 f 5 3 6 s 5 6)
)


(defrule borrarNoNumeroVector
	?y<-(datos $?cabeza ?x&~:(numberp ?x) $?cola)
	=>
	(retract ?y)
	(assert (datos $?cabeza $?cola))

)