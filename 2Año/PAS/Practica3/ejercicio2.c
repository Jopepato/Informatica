#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>


void imprimirAyuda(){
	printf("Uso del programa: ejercicio2 [opciones]\n");
	printf("Opciones:\n");
	printf("-h, --help\t Imprimir esta ayuda\n");
	printf("-g, --group=GRUPO\t Grupo a analizar\n");
	printf("-e, --english\t Mensajes en ingles\n");
	printf("-s, --spanish\t Mensajes en castellano\n");
}

int main(int argc, char ** argv){

	//En este programa usaremos el getoptlong

	int c;
	char * usuario;
	int gid;
	struct group *gr;
	struct passwd *pw;
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"group",	 required_argument,	   0, 'g'},
		{"english",  no_argument,	   0, 'e'},
		{"spanish",  no_argument, 0, 's'},
		{"help",  no_argument, 0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

	int gflag = 0;
	int eflag = 0;
	int sflag = 0;


	int option_index = 0;
	

	while ((c = getopt_long (argc, argv, "eshg:", long_options, &option_index))!=-1)
	{

		if (c == -1)
			break;

		switch (c)
		{

		case 'g':
			gflag=1;
			if((gr=getgrnam(optarg))==NULL){
				printf("Nombre del grupo introducido invalido\n");
				exit(-1);
			}
			break;

		case 'e':
			
			if(sflag==0){
				eflag=1;
			}else{
				printf("No se puede seleccionar dos idiomas a la vez\n");
				exit(-1);
			}

			break;

		case 's':
			
			if(eflag==0){
				sflag=1;
			}else{
				printf("No se pueden seleccionar dos idiomas a la vez\n");
				exit(-1);
			}

			break;

		case 'h':
			imprimirAyuda();
			exit(-1);
			break;

		case '?':
			imprimirAyuda();
			exit(-1);
			break;

		default:
			abort ();
		}
	}


	//Ahora comprobamos las banderas
	if(gflag==0){
		//No se ha introducido un nombre de grupo asi que cogemos el del actor principal
		usuario = getenv("USER");
		pw = getpwnam(usuario);
		gid = pw->pw_gid;
		gr = getgrgid(gid);
	}

	if(eflag==0 && sflag==0){
		//No se ha introducido el idioma, asi que lo comprobamos
		if (strstr(getenv("LANG"),"ES")){
	        sflag=1;
	    }else{
	        eflag=1;
	    }
	}

	//Ahora depende del idioma:
	if(sflag==1){
		//En español
		printf("Identificador de grupo: %d\n", gr->gr_gid);
		printf("Nombre de grupo: %s\n", gr->gr_name);

	}else{
		//En ingles
		printf("Group's identifier: %d\n", gr->gr_gid);
		printf("Group's name: %s\n", gr->gr_name);
	}

return 0;
}