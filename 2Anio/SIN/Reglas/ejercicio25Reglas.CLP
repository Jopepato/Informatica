(defmodule MAIN(export ?ALL))

(deftemplate reina
	(slot id)
	(slot fil (allowed-values 1 2 3 4 5 6 7 8))
	(slot col (allowed-values 1 2 3 4 5 6 7 8)))

(deftemplate tablero
	(slot id)
	(multislot reinas))

(defrule empiezaEsto
	=>
	(focus INICIALIZACION ITERA_EN_FRONTERA IMPRIMESOLUCION))


(defmodule INICIALIZACION (import MAIN ?ALL)
	(export ?ALL))

(deffacts valoresIniciales
	(tamanioTablero 8)
	(pos 1)
	(nextIdReina 1)
	(nextIdTablero 1)
	(tablero (id 0) (reinas))
	(frontera 0)
	(actual 0))


(defrule creaPosicion
	(pos ?x)
	(tamanioTablero ?y)
	(test (< ?x ?y))
	=>
	(assert (pos (+ ?x 1))))

(defmodule ITERA_EN_FRONTERA (import MAIN ?ALL)
		(import INICIALIZACION ?ALL))

(defrule eliminaActual
	?h<-(actual ?)
	=>
	(retract ?h))

(defrule reglaIteraFrontera
	
	;Encontrar el tablero solucion
	(tamanioTablero ?tamanioTablero)
	(not (and
		(tablero (id ?idTablero) (reinas $?reinas))
		(test (= ?tamanioTablero (length$ $?reinas)))))


	?h<-(frontera ?x $?resto)
	(not (actual ?))
	=>
	(retract ?h)
	(assert (frontera $?resto))
	(assert (actual ?x))
	(focus GENERA_HIJOS)
)

(defmodule GENERA_HIJOS
	(import MAIN ?ALL)
	(import INICIALIZACION ?ALL))

(deffunction se-atacan
	(?f ?c ?f2 ?c2)
	(if (or
		(= ?f ?f2)
		(= ?c ?c2)
		(= (+ ?f ?c) (+ ?f2 ?c2))
		(= (- ?f ?c)(- ?f2 ?c2))
		)
	then TRUE
	else FALSE
	)
)


(defrule generaUnHijoSuponiendoQueExisteLaReina
	(actual ?x)
	(tablero (id ?x) (reinas $?reinas))
	?h<-(frontera $?nodos)
	
	(pos ?f)
	(pos ?c)
	(reina (id ?idReina) (fil ?f) (col ?c))
	(foralll (and
			(tablero (id ?x) (reinas $? ?unaReina $?))
			(reina (id ?unaReina) (fil ?f2) (col ?c2)))

			(not (se-atacan ?f ?c ?f2 ?c2)))

	=>
	(assert (tablero (id ?nuevoIdTablero) (reinas $?reinas ?idReina)))
	(retract ?h)
	(assert (frontera ?nuevoIdTablero $?nodos))
	(assert (nextIdTablero (+ ?nuevoIdTablero 1)))	
	)


(defrule generaUnHijoSuponiendoQueLaReinaNOExiste
	(actual ?x)
	(tablero (id ?x) (reinas $?reinas))
	?h<-(frontera $?nodos)
	?h2<-(nextIdTablero ?nuevoIdTablero)
	?h3<-(nextIdReina ?nuevoIdReina)
	
	(pos ?f)
	(pos ?c)
	(not (reina (id ?idReina) (fil ?f) (col ?c)))
	(foralll (and
			(tablero (id ?x) (reinas $? ?unaReina $?))
			(reina (id ?unaReina) (fil ?f2) (col ?c2)))

			(not (se-atacan ?f ?c ?f2 ?c2)))

	=>
	(assert (reina (id ?nuevoIdReina) (fil ?f) (col ?c)))
	(assert (tablero (id ?nuevoIdTablero) (reinas $?reinas ?nuevoIdReina)))
	(retract ?h ?h2 ?h3)
	(assert (frontera ?nuevoIdTablero $?nodos))
	(assert (nextIdTablero (+ ?nuevoIdTablero 1)))
	(assert (nextIdReina (+ ?nuevoIdReina 1)))
	)



(defmodule IMPRIMESOLUCION (import MAIN ?ALL)
			(import (INICIALIZACION ?ALL))

(defrule imprimeSolucion
	
	;Encontrar el tablero solucion
	(tamanioTablero ?tamanioTablero)
	(tablero (id ?idTablero) (reinas $?reinas))
	(test (= ?tamanioTablero (length$ $?reinas)))

	;Seleccionar una reina de ese tablero
	(tablero (id ?idTablero) (reinas $? ?unaReina $?))
	(reina (id ?unaReina) (fil ?f) (col ?c))
	=>
	(printout t ?f ", " ?c crlf))