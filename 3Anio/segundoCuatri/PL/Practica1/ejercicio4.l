/***********************EJERCICIO 4***********/
%{
   /* Descripcion:
    	El analizador léxico recogerá un fichero de entrada y una palabra dada por argumento y contara el numero de veces
	que aparece dicha palabra en el fichero
   */

	//Declaramos las variables globales que vamos a usar
	#include <stdio.h>
	#include <string.h>
	char * palabraUsuario;
	int palabras = 0;
%}
espacio		[ \t]
espacios		{espacio}+
caracter		[a-zA-Z0-9]
palabra		{caracter}+
linea			[\n]
%%
{palabra} {if(strcmp(yytext, palabraUsuario)==0){
			palabras++;		
		}}
.|\t|\n		{;}


%%


int main(int argc, char ** argv){

	if(argc==3){
		yyin=fopen(argv[1],"r");
		palabraUsuario = argv[2];
		yylex();
		printf("Numero de palabras coincidentes: %d\n", palabras);
		
	}else{
		printf("La forma de llamar a este programa es:\n");
		printf("(Nombre de Programa) (Fichero de entrada) (Palabra a buscar)\n");
	}

return 0;
}
