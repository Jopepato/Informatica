%{
#include "macros.h"
#include "ejemplo.h"
#include "ejemplo.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
numero	[0-9]
numero	{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
letra         [a-zA-Z]
caracter		({letra}|{numero})
identificador {letra}{caracter}*(_{caracter}{caracter}*)*
_mod		(?i:_mod)
_div		(?i:_div)
_o			(?i:_o)
_y 			(?i:_y)
_no			(?i:_no)
_borrar		(?i:_borrar)
_lugar		(?i:_lugar)



%x ESTADO_COMENTARIO_LINEAS
%x ESTADO_COMENTARIO_UNA_LINEA
%x ESTADO_CADENA


%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}		 {	double d;  
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
";"		{return FIN_SENTENCIA;}
{":="}      {return ASIGNACION;}
{_mod}		{return MODULO;}
{_div}		{return DIVISION;}
{_o}		{return DISYUCION_LOGICA;}
{_y} 		{return CONJUNCION_LOGICA;}
{_no}		{return NEGACION_LOGICA;}
{_borrar}	{return BORRAR;}
{_lugar}	{return LUGAR;}



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
