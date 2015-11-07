#include "funciones.h"

void main(){

srand(time(NULL));


/*
int ** carton;

carton = generaCarton();

muestraCarton(carton);
*/

char usuario[50] = "ruben";
char password[50] = "josito";
int kk;


kk = compruebaUsuarioPassword("ruben", "josito");

	if(kk==1){
		printf("Todo bien\n");
	}else{
		printf("Adios\n");
	}

}