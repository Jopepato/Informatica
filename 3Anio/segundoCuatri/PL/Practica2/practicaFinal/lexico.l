%{
#include "macros.h"
#include "final.h"
#include "final.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
digito        [0-9]
letra         [a-zA-Z]
caracter		[a-zA-Z0-9]
identificador		{letra}{caracter}*(_{caracter}{caracter}*)*
numero	{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
_div	(?i:_div)
_mod	(?i:_mod)
_o 		(?i:_o)
_y 		(?i:_y)
_no		(?i:_no)
_borrar	(?i:_borrar)
_lugar	(?i:_lugar)

%x ESTADO_COMENTARIO_LINEAS
%x ESTADO_COMENTARIO
%x ESTADO_CADENA

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+ {double d;  
                                   sscanf(yytext,"%lf",&d);
                                 /* Instala el numero en la tabla de simbolos */
				   yylval.sym=install1("",NUMBER,d); 
				   return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install1(yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

">="	{return MAYOR_IGUAL;}
"<="	{return MENOR_IGUAL;}
"="	{return IGUAL;}
"<>"	{return DISTINTO;}
">"	{return MAYOR_QUE;}
"<"	{return MENOR_QUE;}
_no	{return NEGACION;}
_o	{return O_LOGICO;}
_y	{return Y_LOGICO;}
":="      {return ASIGNACION;}
"**"	{return POTENCIA;}
"||" 	{return CONCATENACION;}
{_div}	{return DIV_ENTERA;}
{_mod}	{return MODULO;}


{_borrar} 	{return _BORRAR;}
{_lugar}	{return _LUGAR;}

"@"		{BEGIN ESTADO_COMENTARIO;}
<ESTADO_COMENTARIO>.	{;}
<ESTADO_COMENTARIO>\n 	{BEGIN 0;}

"#"		{BEGIN ESTADO_COMENTARIO_LINEAS;}
<ESTADO_COMENTARIO_LINEAS>"#" 	{BEGIN 0; ;}	
<ESTADO_COMENTARIO_LINEAS>.	{;}
<ESTADO_COMENTARIO_LINEAS>\n 	{;}

"'"	                  {
			    /* Se activa el reconocimiento de la cadena */
			    BEGIN ESTADO_CADENA;
			    yymore();
			  }


<ESTADO_CADENA>"'"        { /* Fin de la cadena: se vuelve al estado por defecto */
			    BEGIN 0; 
			    char * c;
			    yytext[yyleng-1] = '\0';
			    c = (char*)malloc(yyleng+1);
			    int i=1, j=0;
			    strcpy(c, yytext);

			    while(c[i]!='\0'){
			    	if( '\\' != c[i]){
			    		c[j] = c[i];
			    	}else{
			    		i++;
			    	if('t' != c[i] && 'n' != c[i]){
			    		c[j] = c[i];
			    	}else{
			    		if('n' == c[i]){
			    			c[j]='\n';
			    		}else{
			    			c[j] = '\t';
			    		}
			    	}
			    	}
			    	i++;
			    	j++;
			    }
			    c[j]='\0';
			    Symbol *s;
                	if ((s=lookup(c)) == 0)
                    	s = install2("", CADENA, c);
          		yylval.sym = s;
                return CADENA;}

<ESTADO_CADENA>"\\\'"     {yymore();}
<ESTADO_CADENA>\t 		  {yymore();}
<ESTADO_CADENA>.          {yymore();}
<ESTADO_CADENA>\n 		  {yymore();}



^&      { 
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


