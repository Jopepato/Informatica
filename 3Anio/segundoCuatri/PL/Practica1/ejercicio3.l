/***********************EJERCICIO 3***********/
%{
   /* Descripcion:
    	El analizador léxico recogerá un fichero de entrada y contará el numero de lineas, caracteres y palabras
	mostrando por pantalla el numero de cada uno al finalizar la ejecucion
   */

	//Declaramos las variables globales que vamos a usar
	#include <stdio.h>
	#include <string.h>
	int caracteres=0;
	int palabras=0;
	int lineas=0;
%}

espacio		[ \t]
espacios		{espacio}+
caracter		[a-zA-Z0-9]
palabra		{caracter}+
linea			[\n]

%%

{espacio}		{caracteres++;}
{palabra}		{palabras++;
				caracteres = caracteres + strlen(yytext);			
			}
{linea}		{lineas++; caracteres++;}

%%

extern FILE *yyin;
int main(int argc, char ** argv){
	
	if(argc==2){
		//Nos ha pasado el nombre de fichero
		yyin=fopen(argv[1],"r");
		yylex();
		//Ahora imprimimos los caracteres,lineas y palabras
		printf("-Caracteres: %d\n", caracteres);
		printf("-Palabras: %d\n", palabras);
		printf("-Lineas: %d\n", lineas);
			
	}else{
		printf("Numero de parametros introducicos incorrecto, necesito el nombre del fichero\n");
	}
return 0;

}

