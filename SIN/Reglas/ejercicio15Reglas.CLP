;Ejercicio 15

(deftemplate sensor
	(slot codigo (type INTEGER) (range 1 10))
	(slot estado (type SYMBOL) (allowed-values correcto incorrecto))
)

(deffacts hechos
	(sensor (codigo 1)(estado correcto))
	(sensor (codigo 2)(estado incorrecto))
	(sensor (codigo 3)(estado correcto))
	(sensor (codigo 4)(estado incorrecto))
	(sensor (codigo 5)(estado correcto))
	(sensor (codigo 6)(estado correcto))
	(sensor (codigo 7)(estado incorrecto))
	(sensor (codigo 8)(estado incorrecto))
	(sensor (codigo 9)(estado correcto))
	(sensor (codigo 10)(estado correcto))
	(contador 0)
)


(defrule advertencia
	 (contador ?x)
	 (test(>= 3 ?x))
	=>
 	(printout t "Tres o mas sensores estan incorrectos" crlf)
)

(defrule sensorMal
	 ?c<-(contador ?x)
	 (sensor(estado incorrecto))
	 (test(< ?x 3))
	=>
 	(retract ?c)
 	(assert(contador (+ ?x 1)))
)