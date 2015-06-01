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
	(compra (id 1) (producto aceite) (cantidad 2))
	(compra (id 1) (producto vinagre) (cantidad 3))
	(compra (id 1) (producto agua) (cantidad 1))
	(compra (id 2) (producto sal) (cantidad 6))
)


;Ahora tenemos que hacer las reglas


(defrule sumaPrecios

	(compra (id ?x) (producto ?nombre) (cantidad ?c))
	(producto (nombre ?nombre) (precio ?p))
	?h<-(factura ?id ?t)
	=>
	(retract ?h)
	(assert (factura ?x (+ (* ?c ?p) ?t)))

)














