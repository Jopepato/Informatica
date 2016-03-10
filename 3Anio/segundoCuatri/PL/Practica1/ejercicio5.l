/***********************EJERCICIO 5***********/
%{
   /* Descripcion:
    	El analizador léxico recogerá un fichero de entrada y una palabra dada por argumento y cambiará dicha palabra por otra palabra
	que aparece dicha palabra en el fichero
   */

	//Declaramos las variables globales que vamos a usar
	#include <stdio.h>
	#include <string.h>
	char * palabraABuscar;
	char * palabraSustituir;
%}
espacio		[ \t]
espacios		{espacio}+
caracter		[a-zA-Z0-9]
palabra		{caracter}+
linea			[\n]
%%

{palabra} {if(strcmp(yytext, palabraABuscar)==0){
			fprintf(yyout, "%s", palabraSustituir);
		}else{
			fprintf(yyout, "%s", yytext);		
		}}
.|\t|\n	{fprintf(yyout, "%s", yytext);}
%%

extern FILE *yyin, *yyout;
int main(int argc, char ** argv){

	if(argc==5){
		yyin=fopen(argv[1],"r");
		yyout=fopen(argv[2], "w");
		palabraABuscar = argv[3];
		palabraSustituir = argv[4];
		yylex();
		
	}else{
		printf("Numero de argumentos introducido incorrectos");
	}

return 0;
}
