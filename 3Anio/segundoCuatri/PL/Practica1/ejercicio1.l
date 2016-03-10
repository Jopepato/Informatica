/***********************EJERCICIO 1***********/
%{
   /* Descripcion:
    	El analizador léxico recogerá un fichero de entrada y sumará 5 a todo numero multiplo de 4
	almacenando dicha informacion en un fichero de salida
   */
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
			if(atoi(yytext)%4 == 0){
				fprintf(yyout, "%d", atoi(yytext)+5);
			}else{
				fprintf(yyout, "%d", atoi(yytext));
			}
		}



%%


extern FILE *yyin, *yyout;
int main(int argc, char ** argv){

	if(argc<=3){
		switch(argc){
			case 2:
				yyin=fopen(argv[1],"r");
				break;

			case 3:
				yyin=fopen(argv[1],"r"); 
           			yyout=fopen(argv[2],"w");
				break;
		}
		yylex();
	}

return 0;
}
