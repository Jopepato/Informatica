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

inicio ([iI][nN][iI][cC][iI][oO])
fin	([fF][iI][nN])
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

/* Definiciones regulares */

%%

{inicio}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,INICIO);}
{fin}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,FIN);}
{__mod}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__MOD);}
{__o}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__O);}
{__y}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__Y);}
{__no}	{fprintf(yyout, "\x1b[35m\n Palabra reservada:\x1b[0m %s --> token %d\n", yytext,__NO);}
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
{numero}     {fprintf(yyout, "\x1b[32m\n Numero: \x1b[0m%s --> token %d\n", yytext,NUMERO);}
%%

