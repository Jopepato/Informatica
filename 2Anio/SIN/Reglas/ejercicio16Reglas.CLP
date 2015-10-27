;Ejercicio16
(deftemplate fecha
	(slot day (type INTEGER)(range 1 31))
	(slot month (type INTEGER)(range 1 12))
	(slot year (type INTEGER)))
)

;30- Septiembre 9, Abril 4, Junio 6, Noviembre 11
;28- Febrero 2

(deffacts fechas
	(fecha (day 31)(month 1)(year 1995))
	(fecha (day 30)(month 1)(year 1990))
	(fecha (day 29)(month 2)(year 2004))
	(fecha (day 29)(month 2)(year 2601))
	(fecha (day 30)(month 2)(year 1600))
	(fecha (day 31)(month 4)(year 2028))
)

(defrule compruebaFecha
	?f<-(fecha (day ?d)(month ?m)(year ?y))
	(or 
		;El dia sea 31 y ese mes no tenga 31 dias	
		(and (test(= ?d 31))
			(or
				(test(= ?m 9))
				(test(= ?m 4))
				(test(= ?m 6))
				(test(= ?m 11))
				(test(= ?m 2))
			)			
		)
		;Que sea febrero y tenga 29 dias, y no sea bisiesto
		(and (not
			(or
				(and 
					(test (= (mod ?y 4) 0))
					(not(test (= (mod ?y 100) 0)))
				)
				(test (= (mod ?y 400) 0))
			)
			)
			(test(= ?m 2))
			(test(= ?d 29))
		)
		;Que sea febrero y tenga 30 dias
		(and (test (= ?m 2))
			(test (= ?d 30))
		)
	)
=>
	(printout t "El año " ?y " no es correcto, cuyo hecho es " ?f crlf)
)