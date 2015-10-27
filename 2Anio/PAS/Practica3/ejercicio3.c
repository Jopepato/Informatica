#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mqueue.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>



//Ejercicio de los mensajes con tuberias
int main(int argc, char ** argv){


	int fildes[2]; //Esta tuberia con dos campos la usaremos para leer y escribir

	pid_t pid;
	int died, status; //Para controlar los procesos
	int vector[5]; //Para leer los 5 numeros aleatorios
	int random; //Para almacenar el numero aleator
	int i;

	//Inicializamos la semilla
	srand(time(NULL));

	status = pipe(fildes);

	if(status==-1){
		printf("Fallo al crear la tuberia\n");
		exit(-1);
	}



	switch(pid=fork()){

		case -1:
			//Ha fallado el fork()
			printf("Fallo al ejecutar fork()\n");
			exit(-1);
			break;


		case 0:
			//El hijo, leera de la tuberia los mensajes
			printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

			close(fildes[1]);

			//Procedemos a leer la tuberia
			for(i = 0; i<5; i++){
				
				read(fildes[0], &vector[i], sizeof(int *));

				printf("[HIJO]: leemos el numero aleatorio %d de la tuberia\n", vector[i]);

			}
			
			close(fildes[0]);
			printf("Tuberia cerrada\n");

			exit(EXIT_SUCCESS);

			break;

		default:
			//El padre, pondra los mensajes en la tuberia

			printf("[PADRE]: Mi PID es %d y el de mi hijo es %d\n", getpid(), pid);

			close(fildes[0]);

			for(i = 0; i< 5; i++){
				random = rand() % 50000;
				printf("[PADRE] Meto %d en la tuberia...\n", random);

				write(fildes[1], &random, sizeof(int *));
				//Con esto ya hemos escrito los 5 numeros aleatorios
				//sleep(5);
			}
			

			close(fildes[1]);

			//Esperamos al hijo para ver si se ha producido algun error
			died=wait(&status);
			printf("[PADRE]: El proceso hijo con PID %d ha salido con código de error %d. Salgo...\n", died, status);
			exit(EXIT_SUCCESS);


			break;


}






return 0;
}