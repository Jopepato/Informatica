(defmodule MAIN (export ?ALL))
(defrule imprimeHOla
	?h<-(initial-fact)
	=>
	(retract ?h)
	(assert (initial-fact))
	(printout t "Hola, soy el moduulo MAIN" crlf)
	(focus A B C))


(defmodule A (import MAIN ?ALL))
(defrule imprimeHola_A
	=>
	(printout t "Hola, soy el modulo A" crlf))


(defmodule B (import MAIN ?ALL))
(defrule imprimeHola_B
	=>
	(printout t "Hola, soy el modulo B" crlf))

(defmodule C (import MAIN ?ALL))
(defrule imprimeHola_C
	=>
	(printout t "Hola, soy el modulo C" crlf))





(defmodule A (export deftemplate reina))
(deftemplate reina(slot fil)(slot col))
(defulre imprimeHola
	=>
	(printout t "Hola" crlf))

(defmodule B(import A deftemplate reina))
(defrule imprimeReina
	;HACER