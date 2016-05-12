%{
#include "macros.h"
#include "ejemplo.h"
#include "ejemplo.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
numero        [0-9]
letra         [a-zA-Z]
caracter		({letra}|{numero})
identificador {letra}{caracter}*(_{caracter}{caracter}*)*
para 		(?ipara)
_mod		(?i_mod)
_div		(?_div)
_o			(?i_o)
_y 			(?i_y)
leer		(?ileer)
leer_cadena		(?ileer_cadena)
escribir		(?iescribir)
si 			(?si)
entonces	(?ientonces)
si_no		(?isi_no)
fin_si 		(?fin_si)
mientras	(?imientras)
hacer		(?imientras)
fin_mientras	(?ifin_mientras)
repetir		(?irepetir)
hasta		(?ihasta)
para 		(?ipara)
desde		(?idesde)
hasta		(?ihasta)
paso		(?ipaso)
fin_para	(?ifin_para)
_borrar		(?_borrar)
_lugar		(?i_lugar)

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */
/* Lo del ?i es para que no haga distinçión entre minusculas y mayusculas */

{numero}+\.?|{numero}*\.{numero}+ {double d;  
                                   sscanf(yytext,"%lf",&d);
                                 /* Instala el numero en la tabla de simbolos */
				   yylval.sym=install("",NUMBER,d); 
				   return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

">="	{return MAYOR_IGUAL;}
"<="	{return MENOR_IGUAL;}
"=="	{return IGUAL;}
"<>"	{return DISTINTO;}
">"		{return MAYOR_QUE;}
"<"		{return MENOR_QUE;}
"!"		{return NEGACION;}
"||"	{return CONCATENACION;}
o_logico	{return O_LOGICO;}
y_logico	{return Y_LOGICO;}
":="      {return ASIGNACION;}
";"		{return FIN_SENTENCIA;}
^#       { 
 	  BORRAR; 
	  LUGAR(10,10);
	  INTENSIDAD;
	  printf(">>>>>>> Fin del programa <<<<<<<\n");
	  APAGA;
	  LUGAR(24,1);

  	  return 0;
	}
\n      {lineno++; } /* no se devuelve nada, continúa el analisis léxico */
.       {return yytext[0];}
