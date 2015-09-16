;Ejercicio 20

(deftemplate habitacion
	(slot id)
	(slot capacidad)
;	(slot numOcupantes)
;	(slot sexo)
;	(slot fumador)
	(multislot ocupantes)
	)

(deftemplate estudiante
	(slot nombre)
	(slot sexo)
	(slot fumador)
	(slot dni)
;	(slot asignado)
	)

(deffacts hechos
	(habitacion (id 1) (capacidad 1))
	(habitacion (id 2) (capacidad 1))
	(habitacion (id 3) (capacidad 3))
	(habitacion (id 4) (capacidad 4))
	(habitacion (id 5) (capacidad 3))
	(estudiante (nombre Pepa) (sexo mujer) (fumador no) (dni 2))
	(estudiante (nombre Paco) (sexo hombre) (fumador no) (dni 4))
	(estudiante (nombre Lucia) (sexo mujer) (fumador si) (dni 7))
	(estudiante (nombre Mario) (sexo hombre) (fumador si) (dni 9))
	(estudiante (nombre Andres) (sexo hombre) (fumador no) (dni 10))
	(estudiante (nombre Paco2) (sexo hombre) (fumador no) (dni 40))
	(estudiante (nombre Lucia2) (sexo mujer) (fumador si) (dni 70))
	(estudiante (nombre Mario2) (sexo hombre) (fumador si) (dni 90))
	(estudiante (nombre Andres2) (sexo hombre) (fumador no) (dni 100))
	(estudiante (nombre Paco3) (sexo hombre) (fumador no) (dni 401))
	(estudiante (nombre Lucia3) (sexo mujer) (fumador si) (dni 701))
	(estudiante (nombre Mario3) (sexo hombre) (fumador si) (dni 901))
	(estudiante (nombre Andres3) (sexo hombre) (fumador no) (dni 1001))
)

(defrule asignarEstudianteHabitacionCompatible
	;Coger estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	;Coger habitacion compatible que tenga espacio
	?h<-(habitacion (id ?id) (capacidad ?c)
		(ocupantes $?oc))
	(test (< (length$ $?oc) ?c))
	(habitacion (id ?id) (ocupantes $? ?dniOcupante $?))
	(estudiante (dni ?dniOcupante) (fumador ?z1) (sexo ?y))
	(test (eq ?z1 ?z))
	
	;No existe una habitacion compatible más grande
	(not (and 
		(habitacion (id ?id2&~?id) (capacidad ?c2)
			(ocupantes $?oc2))
		(test (< (length$ $?oc2) ?c2))
		(habitacion (id ?id2) (ocupantes $? ?dniOcupante2 $?))
		(estudiante (dni ?dniOcupante2) (fumador ?z12) (sexo ?y))
		(test (eq ?z12 ?z))
		(test (> ?c2 ?c))))
	=>
	;Hacer la asignacion del estudiante a la habitacion
	(modify ?h (ocupantes $?oc ?dni))
)


(defrule asignarEstudianteHabitacionVaciaGrande
	;Coger estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	;Coger una habitacion vacía
	?h<-(habitacion (id ?id) (ocupantes $?oc) (capacidad ?c))
	(test (= (length$ $?oc) 0))

	;no existe una habitacion vacía más grande
	(not (habitacion (ocupantes) (capacidad ?c2&:(> ?c2 ?c))))

	;no existe una habitacion compatible
	(not (and 
		(habitacion (id ?id2) (capacidad ?c2)
			(ocupantes $?oc2))
		(test (< (length$ $?oc2) ?c2))
		(habitacion (id ?id2) (ocupantes $? ?dniOcupante $?))
		(estudiante (dni ?dniOcupante) (fumador ?z1) (sexo ?y))
		(test (eq ?z1 ?z))))
	=>
	;Asignar el estudiante a la habitación
	(modify ?h (ocupantes ?dni))
)



(defrule noSePuedeAlojarAEstudiante
	;Coger estudiante no asignado a ninguna habitacion
	(estudiante (nombre ?x) (sexo ?y) (fumador ?z) (dni ?dni))
	(not (habitacion (ocupantes $? ?dni $?)))

	;No existe habitación vacía
	(not (habitacion (ocupantes)))

	;No existe habitación compatible que tenga espacio
	(not (and 
		(habitacion (id ?id) (capacidad ?c)
			(ocupantes $?oc))
		(test (< (length$ $?oc) ?c))
		(habitacion (id ?id) (ocupantes $? ?dniOcupante $?))
		(estudiante (dni ?dniOcupante) (fumador ?z1) (sexo ?y))
		(test (eq ?z1 ?z))))
	=>
	(printout t "No se puede alojar a " ?x "(dni: " ?dni ")" crlf)
)
