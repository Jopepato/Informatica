;Ejercicio 20 de reglas
;Ejercicio de las habitaciones
;Terminar en casa :>

(deftemplate estudiante
	(slot nombre)
	(slot sexo)
	(slot fumador)
	(slot dni)
)

(deftemplate habitacion
	(slot id)
	(slot capacidad)
	(multislot ocupantes)
)


(deffacts hechos
	(habitacion (id 1) (capacidad 1))
	(habitacion (id 2) (capacidad 1))
	(habitacion (id 3) (capacidad 3))
	(habitacion (id 4) (capacidad 4))
	(habitacion (id 5) (capacidad 3))
	(estudiante (nombre Pepa) (sexo mujer) (fumador no) (dni 2))
	(estudiante (nombre Pepe) (sexo hombre) (fumador si) (dni 3))
	(estudiante (nombre Luisa) (sexo mujer) (fumador si) (dni 4))
	(estudiante (nombre Paco) (sexo hombre) (fumador no) (dni 5))
	(estudiante (nombre Fran) (sexo hombre) (fumador si) (dni 6))
	(estudiante (nombre Ruben) (sexo hombre) (fumador no) (dni 7))
	(estudiante (nombre Ana) (sexo mujer) (fumador si) (dni 8))
	(estudiante (nombre Isabel) (sexo mujer) (fumador no) (dni 9))
)

(defrule asignarEstudianteHabitacionCompatible
	;Coger estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	;Coger habitacion compatible que tenga espacio
	(habitacion (capacidad ?c) (ocupantes $?oc))
		(test (< (length$ $?oc) (?c))
	(habitacion (id ?id) (ocupantes $? ?dniOcupante $?))
	(estudiante (dni ?dniOcupante) (fumador ?z) (sexo ?y))
	
	=>
	;Hacer la asignacion del estudiante a la habitacion
	(modify ?h (ocupantes $?oc ?dni))

)

(defrule asignarEstudianteHabitacionVaciaGrande
	;Coger un estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	;Coger una habitacion vacia
	?h<-(habitacion (id ?id) (ocupantes) (capacidad ?c))

	;No existe una habitacion vacia mas grande
	(not (habitacion (ocupantes) (capacidad ?c2&:(> ?c2 ?c))))

	=>
	;Asignar el estudiante a la habitacion
	(modify ?h (ocupantes ?dni))
)

(defrule noSePuedeAlojarAEstudiante
	;Coger estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	(not (habitacion (ocupantes))

	(not (and
		(habitacion (od ?id) (capacidad ?c)
			(ocupantes $?oc))
		(test (< (length$ $?oc) ?c))
		(habitacion (id ?id2) (ocupantes $? ?dniOcupante $?))
		(estudiante (dni ?dniOcupante) (fumador ?z1) (sexo ?y))

	=>
	(printout t "No se pue, vamos que no se pue" crlf)

)
