#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){

	int c;
	//Declaramos algunas banderas para las variables que no pueden ir juntas
	int nflag = 0;
	int uflag = 0;
	int gflag = 0;
	int eflag = 0;
	int sflag = 0;




	while((c = getopt(argc, argv, "n:u:ges") != -1){



		//Y aqui cogemos la opcion que deseamos

		switch(c){

			case 'n':

				break;

			case 'u':

				break;


			case 'g':

				break;

			case 'e':

				break;

			case 's':


				break;

			case '?':
					printf("Argumento invalido o argumento necesita una cadena como complementario :>");
				break;

		}

	}


}