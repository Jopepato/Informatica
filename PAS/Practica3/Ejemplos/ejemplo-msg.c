#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/msg.h>

#define ID_COLA 1500

int main() {
	// Para realizar el fork
	pid_t rf;

	// Longitud del mensaje
	int longitudMensaje;

	// Para controlar los valores devueltos por las funciones (control de errores)
	int resultado;

	// Estructura que representa el mensaje
	struct {
		long prioridad;   // Este primer long es obligatorio
		int numeroAleatorio;
	} mensaje;

	// Descriptor de la cola
	int desCola;

	// La longitud del mensaje es el tamaño de la estructura
	longitudMensaje = sizeof(mensaje);

	// Creamos la cola de mensajes, si la cola ya existía, se me devuelve
	desCola = msgget(ID_COLA, 0600 | IPC_CREAT);
	if(desCola==-1){
		printf("\nERROR al crear la cola.\n");
		exit(1);
	}
	
	rf = fork();
	switch (rf)
	{
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);

		case 0:
			printf ("[HIJO]: mi PID es %d y mi PPID es %d\n", getpid(), getppid());
			
			// Rellenamos los campos del mensaje que vamos a enviar
			mensaje.prioridad = 1;
			srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual
			mensaje.numeroAleatorio = rand()%5000; //Número aleatorio entre 0 y 4999
			printf("[HIJO]: genero el número aleatorio %d\n", mensaje.numeroAleatorio);

			printf("[HIJO]: enviando mensaje (espera bloqueante)...\n");
			// Mandamos el mensaje			
			resultado = msgsnd( desCola, &mensaje, longitudMensaje, 0);
			if(resultado != 0){
				printf("\n[HIJO]: ERROR al enviar el mensaje.\n");
				exit(1);
			}

			printf("[HIJO]: Mensaje enviado! Salgo...\n");
			break;

		default:
			printf ("[PADRE]: mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			printf ("[PADRE]: recibiendo mensaje (espera bloqueante)...\n");

			// Recibimos un mensaje a través de la cola
			resultado = msgrcv( desCola, &mensaje, longitudMensaje, 1, 0);
			if(resultado != longitudMensaje){
				printf("\n[PADRE]: ERROR al recibir el mensaje.\n");
				exit(1);				
			}
			
			// Imprimimos el campo idProceso que viene en el mensaje
			printf("[PADRE]: el número aleatorio que viene en el mensaje es %d\n", mensaje.numeroAleatorio);

			// Eliminar la cola
			resultado = msgctl(desCola, IPC_RMID, 0);
			if(resultado != 0){
				printf("\n[PADRE]: ERROR eliminando la cola\n");
				exit(1);
			}
			printf("[PADRE]: Cola cerrada. Salgo...\n");
	}

	exit(0);
}
