/***********************EJERCICIO 2***********/
%{
   /* Descripcion:
    	El analizador léxico recogerá un fichero de entrada y sumará N1 (numero pasador por parametro) a los multiplos de N2
	que tambien van a ser pasados por argumento
   */

	//Declaramos las variables globales que vamos a usar
	int n1 = 0;
	int n2 = 0;
	#include <stdio.h>
%}

espacio		[ \t\n]
espacios		{espacio}+
letra			[a-zA-Z]
digito		[0-9]
identificador	{letra}({letra}|{digito})*
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

%%
{espacios}|{identificador} {fprintf(yyout, "%s", yytext);}
{numero}	{
			if(atoi(yytext)%n2 == 0){
				fprintf(yyout, "%d", atoi(yytext)+n1);
			}else{
				fprintf(yyout, "%d", atoi(yytext));
			}
		}
%%


extern FILE *yyin, *yyout;
int main(int argc, char ** argv){

	if(argc==5){
		
		yyin=fopen(argv[1],"r"); 
           	yyout=fopen(argv[2],"w");
		n1 = atoi(argv[3]);
		n2 = atoi(argv[4]);
		yylex();
	}else{
		printf("Se necesita como parametros, fichero de entrada, de salida, n1 y n2\n");
	}
	
return 0;	
}

