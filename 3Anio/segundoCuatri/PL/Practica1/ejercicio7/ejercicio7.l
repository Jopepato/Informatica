/**************************** ejemplo7.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * El analizador lexico reconoce elementos de un lenguaje de programacion
      * Permite leer desde un fichero y escribir la salida en otro fichero
	* Leera los elementos del pseudocodigo

   */
#include <stdio.h>
#include "ejercicio7.h"   /* declaracion de los componentes lexicos o tokens */
%}

espacios	[ \t]
inicio 	([iI][nN][iI][cC][iI][oO])
fin		([fF][iI][nN])
__mod	(__[mM][oO][dD])
__o	(__[oO])
__y	(__[yY])
__no	(__[nN][oO])
leer	([lL][eE][eE][rR])
escribir	([eE][sS][cC][rR][iI][bB][iI][rR])
si	([sS][iI])
entonces	([eE][nN][tT][oO][nN][cC][eE][sS])
si_no		([sS][iI]_[nN][oO])
fin_si	([fF][iI][nN]_[sS][iI])
mientras	([mM][iI][eE][nN][tT][rR][aA][sS])
hacer		([hH][aA][cC][eE][rR])
fin_mientras	([fF][iI][nN]_[mM][iI][eE][nN][tT][rR][aA][sS])
repetir	([rR][eE][pP][eE][tT][iI][rR])
hasta_que	([hH][aA][sS][tT][aA]_[qQ][uU][eE])
para		([pP][aA][rR][aA])
desde		([dD][eE][sS][dD][eE])
hasta		([hH][aA][sS][tT][aA])
paso		([pP][aA][sS][oO])
fin_para	([fF][iI][nN]_[pP][aA][rR][aA])
digito	[0-9]
numero	{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
letra	[a-zA-Z]
caracter	[0-9a-zA-Z]
identificador_Bueno	^{letra}{caracter}*(_{caracter}{caracter}*)*
identificador_Malo	^{letra}({caracter}*|__+)*{caracter}*_*
identificador_Malo2	^{numero}({caracter}*|_*|__+)*{caracter}*
comentario_una_linea	^\#.*
numero_Mal	(^{digito}+|\.+)({digito}+|_*|\.+)*{digito}*



%x ESTADO_COMENTARIO
%x ESTADO_CADENA
/* Definiciones regulares */

%%
{espacios}	{;}
\n 			{;}
{inicio}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,INICIO);}
{fin}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,FIN);}
{__mod}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__MOD);
		fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m%s --> token %d\n", yytext, MODULO);}

{__o}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__O);
		fprintf(yyout, "\x1b[32m\n Operador lógico: \x1b[0m %s --> token %d\n", yytext, __O);}

{__y}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__Y);
		fprintf(yyout, "\x1b[32m\n Operador lógico: \x1b[0m %s --> token %d\n", yytext, __Y);}

{__no}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__NO);
		fprintf(yyout, "\x1b[32m\n Operador lógico: \x1b[0m %s --> token %d\n", yytext, __NO);}

{leer}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,LEER);}
{escribir}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,ESCRIBIR);}
{si}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,SI);}
{entonces}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,ENTONCES);}
{si_no}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,SI_NO);}
{fin_si}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,FIN_SI);}
{mientras}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,MIENTRAS);}
{hacer}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,HACER);}
{fin_mientras}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,FIN_MIENTRAS);}
{repetir}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,REPETIR);}
{hasta_que}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,HASTA_QUE);}
{para}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,PARA);}
{desde}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,DESDE);}
{hasta}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,HASTA);}
{paso}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,PASO);}
{fin_para}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,FIN_PARA);}
{numero}     {fprintf(yyout, "\x1b[32m\n Numero: \x1b[0m %s --> token %d\n", yytext,NUMERO);}
{numero_Mal}	{fprintf(yyout, "\x1b[31m\n Error, numero mal especificado\x1b[0m %s\n", yytext);}

":="	{fprintf(yyout, "\x1b[32m\n Operador de asignación: \x1b[0m %s --> token %d\n", yytext, ASIGNACION);}
"+"		{fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m %s --> token %d\n", yytext, SUMA);}
"-"		{fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m %s --> token %d\n", yytext, RESTA);}
"*"		{fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m %s --> token %d\n", yytext, PRODUCTO);}
"/"		{fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m %s --> token %d\n", yytext, DIVISION);}
"**"	{fprintf(yyout, "\x1b[32m\n Operador aritmético: \x1b[0m %s --> token %d\n", yytext, POTENCIA);}
"||"	{fprintf(yyout, "\x1b[32m\n Operador alfanumérico: \x1b[0m %s --> token %d\n", yytext, CONCATENACION);}

"<"		{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, MENOR_QUE);}
"<="	{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, MENOR_IGUAL_QUE);}
">"		{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, MAYOR_QUE);}
">="	{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, MAYOR_IGUAL_QUE);}
"=="	{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, IGUAL);}
"<>"	{fprintf(yyout, "\x1b[32m\n Operador relacional: \x1b[0m %s --> token %d\n", yytext, DISTINTO);}
";"		{fprintf(yyout, "\x1b[32m\n Componente léxico: \x1b[0m%s --> token %d\n", yytext, FIN_SENTENCIA);}
"("		{fprintf(yyout, "\x1b[32m\n Componente léxico: \x1b[0m%s --> token %d\n", yytext, PARENTESIS_IZQ);}
")"		{fprintf(yyout, "\x1b[32m\n Componente léxico: \x1b[0m%s --> token %d\n", yytext, PARENTESIS_DER);}

{comentario_una_linea} 	{fprintf(yyout, "\x1b[32m\n Comentario de una linea: \x1b[0m%s --> token %d\n", yytext, COMENTARIO_UNA_LINEA);}

"(*"	{BEGIN ESTADO_COMENTARIO;
		yymore();}
<ESTADO_COMENTARIO>(.|\n)	yymore();
<ESTADO_COMENTARIO>"(*" {fprintf(yyout, "\x1b[31m\n Error, no se pueden anidar comentarios\x1b[0m\n");}
<ESTADO_COMENTARIO>"*)"	{BEGIN 0;
						//Se ha acabado el comentario
						fprintf(yyout, "\x1b[32m\n Comentario: \x1b[0m%s --> token %d\n", yytext, COMENTARIO);}


"'"	                  {
			    /* Se activa el reconocimiento de la cadena */
			    BEGIN ESTADO_CADENA; 
			  }


<ESTADO_CADENA>"'"        { /* Fin de la cadena: se vuelve al estado por defecto */
			    BEGIN 0; 
			    yytext[yyleng-1]='\0';
			    fprintf(yyout, "\x1b[32m\n Cadena: \x1b[0m%s --> token %d\n", yytext, CADENA);
			  }      
<ESTADO_CADENA>"\\\'"     {yymore();}
<ESTADO_CADENA>.          {yymore();}
<ESTADO_CADENA>\n         {yymore();}

{identificador_Bueno}		{fprintf(yyout, "\x1b[32m\n Identificador: \x1b[0m%s --> token %d\n", yytext, IDENTIFICADOR);}
{identificador_Malo}		{fprintf(yyout, "\x1b[31m\n Error, Identificador mal escrito\x1b[0m %s\n", yytext);}
{identificador_Malo2}		{fprintf(yyout, "\x1b[31m\n Error, Identificador mal escrito\x1b[0m %s\n", yytext);}

.						{fprintf(yyout, "\x1b[31m\n Error, componente no reconocido\x1b[0m %s\n", yytext);}
%%

extern FILE *yyin, *yyout;
int main(int argc, char ** argv){

	if(argc==2||argc==3){
		switch(argc){
			case 2:
				yyin=fopen(argv[1],"r");
				yylex();
				break;

			case 3:
				yyin=fopen(argv[1],"r");
				yyout=fopen(argv[2], "w");
				yylex();
				break;
		}
	}else{
		//El numero de parametros es incorrecto
		printf("La forma de llamar a este programa es:\n");
		printf("(Nombre de Programa) (Fichero de entrada) (Fichero de salida)*Opcional*\n");
	}

return 0;
}
