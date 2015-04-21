#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char ** argv){

	int c;
	//Declaramos algunas banderas para las variables que no pueden ir juntas
	char * value;
	struct passwd *pw;//Para obtener la informacion del usuario
	struct group *gr;//Para obtener la informacion del grupo
	char * login;
	int uid;
	int nflag = 0;
	int uflag = 0;
	int gflag = 0;
	int eflag = 0;
	int sflag = 0;




	while((c = getopt(argc, argv, "gesn:u:")) != -1){



		//Y aqui cogemos la opcion que deseamos

		switch(c){

			case 'n':
				if(uflag==0){
					nflag=1;
					login = optarg;
				}else{
					printf("Las opciones -n y -u no pueden ir juntas\n");
					exit(-1);
				}

				break;

			case 'u':
				if(nflag==0){
					uflag=1;
					uid = atoi(optarg);
				}else{
					printf("Las opciones -n y -u no pueden ir juntas\n");
					exit(-1);
				}
				break;


			case 'g':
					gflag=1;
				break;

			case 'e':
					if(sflag == 0){
						eflag = 1;
					}else{
						printf("No puede seleccionar dos idiomas a la vez\n");
						exit(-1);
					}
				break;
			case 's':
					if(eflag==0){
						sflag=1;
					}else{
						printf("No puede seleccionar dos idiomas a la vez\n");
					}


				break;

			case '?':
					printf("Argumento invalido o argumento necesita una cadena como complementario :>\n");
					exit(-1);
				break;

		}

	}

	//Aqui comprobamos las banderas
	
	//Comprobamos el idioma
	if((eflag==0)&&(sflag==0)){
		value = getenv("LANG");		
	   
	   if (strstr(value,"ES")){
	        sflag=1;
	    }else{
	        eflag=1;
	    }
	}

	//Comprobamos que el usuario o el id proporcionados son correctos
	if(nflag==1){
		if ((pw = getpwnam(login)) == NULL)
        {
            printf("Nombre de usuario incorrecto.\n");
            exit(1);
        }
	}

	if(uflag==1){
		if ((pw = getpwuid(uid)) == NULL)
        {
            printf("Numero de usuario incorrecto.\n");
            exit(1);
        }
	}

	if(nflag== 0 && uflag == 0){
		//No se ha proporcionado ni el nombre del usuario ni el uid
		login = getenv("USER");
		pw = getpwnam(login);
	}

	//Hacemos dos para mostrar en español o en ingles

	if(sflag==1){


		printf("Nombre de usuario: %s\n", pw->pw_gecos);
		printf("Identificador de usuario: %i\n", pw->pw_uid);
		printf("Contraseña: %s\n", pw->pw_passwd);
		printf("Carpeta de inicio: %s\n", pw->pw_dir);
		printf("Interprete por defecto: %s\n", pw->pw_shell);

		if(gflag==1){
			gr = getgrgid(pw->pw_gid);
			printf("Numero del grupo principal: %i\n", pw->pw_gid);
			printf("Nombre del grupo principal: %s\n", gr->gr_name);
		}

	}else{


		printf("User's name: %s\n", pw->pw_gecos);
		printf("User's identifier: %i\n", pw->pw_uid);
		printf("Password: %s\n", pw->pw_passwd);
		printf("Home: %s\n", pw->pw_dir);
		printf("Default shell: %s\n", pw->pw_shell);

		if(gflag==1){
			gr = getgrgid(pw->pw_gid);
			printf("Main Group Number: %i\n", pw->pw_gid);
			printf("Main Group Name: %s\n", gr->gr_name);
		}
	}

	return 0;
}