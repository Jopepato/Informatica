;Ejercico 23
;Ejercicio del supermercado

(deftemplate producto
	(slot nombre)
	(slot precio)
)

(deftemplate compra
	(slot id)
	(slot producto)
	(slot cantidad)
	(slot comprobado)
)

(deftemplate factura
	(slot id)
	(slot precio)
)


(deffacts compras
	(producto (nombre aceite) (precio 2))
	(producto (nombre vinagre) (precio 3))
	(producto (nombre sal) (precio 1))
	(producto (nombre agua) (precio 2))
	(compra (id 1) (producto aceite) (cantidad 2) (comprobado 0))
	(compra (id 1) (producto vinagre) (cantidad 3) (comprobado 0))
	(compra (id 1) (producto agua) (cantidad 1) (comprobado 0))
	(compra (id 2) (producto sal) (cantidad 6) (comprobado 0))
)


;Ahora tenemos que hacer las reglas

;En esta oferta veremos la cantidad y la cambiaremos a las unidades oportunas
(defrule oferta3x2

	?c<-(compra (id ?x) (producto ?nombre) (cantidad ?y) (comprobado ?z))
	(test (eq ?z 0))
	(test(>= (/ ?y 3) 1))
	=>
	(modify ?c (cantidad (- ?y (/ ?y 3))) (comprobado 1))
)

(defrule noOferta3x2
	?c<-(compra (id ?x) (producto ?nombre) (cantidad ?y) (comprobado ?z))
	(test (eq ?z 0))
	(not(test(>= (/ ?y 3) 1)))
	=>
	(modify ?c (comprobado 1))
)


(defrule creaFacturas
	(compra (id ?x))
	(not (factura (id ?x)))
	=>
	(assert (factura (id ?x) (precio 0)))
)


(defrule sumaPrecios
	?h<-(factura (id ?x) (precio ?total))
	?compra<-(compra (id ?x) (producto ?nombre) (cantidad ?c) (comprobado ?z))
	(producto (nombre ?nombre) (precio ?p))
	(test (eq ?z 1))
	=>
	(retract ?h)
	(retract ?compra)
	(assert (factura (id ?x) (precio (+ (* ?c ?p) ?total))))

)