(deftemplate fecha
	(slot dia (type INTEGER)(range 1 31))
	(slot mes (type INTEGER)(range 1 12))
	(slot anyo (type INTEGER))
)

(deffacts fechas
	(fecha (dia 27)(mes 4)(anyo 2015))
	(fecha (dia 31)(mes 5)(anyo 2914))
)



(defrule compruebaFecha "Regla que comprueba que la fecha este correcta"
	(fecha(dia ?x)(mes ?y)(anyo ?z))

	
	;Comprobar que el año es 31 para meses que no tienen 31 dias
	

)