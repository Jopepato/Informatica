;Ejercicio 13

;Lo tenemos que hacer con un forall


;La opcion facil seria con el not y el forall

;Sin forall
(defrule ordena
	(dato ?x&:(numero ?x))
	(not(todoslosdatos $? ?x $?))
	(?d <-(todoslosdatos $?value)
;Proseguir


(forall (dato ?y&(< ?y ?x))
	(todosdatos $? ?y $?)
)