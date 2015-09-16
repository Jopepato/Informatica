(deffacts constructor 
"mi constructor"
(datos 2 1 3)
(datos 4 8)
(datos 6 11 8 20)
)
(defrule reglaVariables
"probando ambito actuacion variables"
(datos ?x&: (numberp ?x)
?y&: (> ?y ?x)
$?z
?x)
=>
(printout t "se disparara mi regla :>, x = " ?x " y= " ?y "comodin: " $?z crlf)
))

(defrule raglapersonalizada
"regla para ver la multiplicacion y esas cosas"
(datos ?x&: (numberp ?x)
?y&: (=(* 2 ?x) ?y)
$?z
?y
)
=>
(printout t "Se dispara mi regla :>, x = " ?x "y(2*x) = " ?y " comodin: " $?z " final: " ?y crlf)
)

(defrule hordenados
"Rule que te dice si un vector esta ordenado :>"
(datos 
$?x&:(numberp $?x)

)
(printout t ":>" $?x crlf) 
)