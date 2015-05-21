(deffacts hecho
	(datos a b c d e f g 1 hola adios yo soy 1 tu 1 padre 1 2 4 1 1 1)
)

(defrule eleminaUno
	?nuevo<-(datos $?cabeza
	 ?x&:(numberp ?x)
	 $?cola)
	(test(= ?x 1))
	=>
	(retract ?nuevo)
	(assert (datos $?cabeza $?cola))
)