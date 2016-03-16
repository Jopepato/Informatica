/***********************EJERCICIO 6***********/
%{
   /* Descripcion:
    	Considerese un fichero de registro que contiene informacion sobre los ficheros escritos en una impresora
	Cada linea tiene una informacion, "usuario fichero fecha hora"
   */

	//Declaramos las variables globales que vamos a usar
#include <stdio.h>
#include <string.h>
char * usuario;
char * dia;
char userAux[512];
int opcion;
int contadorUsuario=0;
int contadorFecha=0;

%}
espacio		[ \t]
espacios		{espacio}+
caracter		[a-zA-Z0-9á-úÁ-Ú]
palabra		{caracter}+
fichero		({palabra}\.{palabra})
fecha			([0-9]{1,2}\/[0-9]{1,2}\/[0-9]{2,4})
hora			([0-9]{2}\:[0-9]{2})
linea			[\n]
%%

{palabra}	{if(opcion==1){
			//Solo contamos el usuario
			if(strcmp(yytext, usuario)==0){
				contadorUsuario++;
			}
		}else{
			//Opcion de usuario mas fecha
			//Copiamos el usuario para mirar despues la fecha
			strcpy(userAux, yytext);
			
		}}

{fichero}	{;}

{fecha}	{if(opcion==2){
			//Opcion con la fecha
			if(strcmp(userAux,usuario)==0){
				//El usuario de esa linea es el que queremos
				//Ahora miramos la fecha
				if(strcmp(dia, yytext)==0){
					//Usuario y fecha coincidentes
					contadorFecha++;
				}
			}
		}}
{hora}	{;}
.|\n		{;}
%%

extern FILE *yyin;
int main(int argc, char ** argv){

	//Hay dos modos de uso, unicamente con el usuario o usuario mas dia
	if(argc==3 || argc==4){
		switch(argc){

			case 3:
				//Fichero mas usuario
				yyin=fopen(argv[1],"r");
				usuario = argv[2];
				opcion = 1;
				yylex();
				printf("Los ficheros impresos por el usuario %s son: %d\n", usuario, contadorUsuario);
				break;


			case 4:
				//Fichero mas usuario mas dia
				yyin=fopen(argv[1],"r");
				usuario = argv[2];
				dia = argv[3];
				opcion = 2;
				yylex();
				printf("Los ficheros impresos por el usuario %s el dia %s son: %d\n", usuario, dia, contadorFecha);
				break;
		}
	}else{
		printf("La forma de llamar a este programa es:\n");
		printf("(Nombre de Programa) (Fichero de entrada) (Nombre de usuario) (Dia a buscar) *Opcional*\n");
	}

return 0;
}
