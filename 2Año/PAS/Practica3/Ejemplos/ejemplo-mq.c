#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_SIZE    5
#define QUEUE_NAME  "/una_cola"

int main() {
	// Descriptor de la cola
	mqd_t mq;
	
	// Buffer para la lectura/escritura
	char buffer[MAX_SIZE + 1];

	// Atributos de la cola
	struct mq_attr attr;

	// Resultado de las operaciones
	int resultado;

	// Para realizar el fork
	pid_t rf;
	int died, status;

	// Numero aleatorio a generar
	int numeroAleatorio;
	
	// Realizar el fork
	rf = fork();

	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	switch (rf)
	{
		// Error
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);

		// Hijo
		case 0:

			/* Apertura de la cola
			   O_CREAT: si no existe, se crea
			   O_RDWR: lectura/escritura
			   O_RDONLY: solo lectura
			   O_WRONLY: solo escritura
			   0644: permisos rw-r--r--
			   attr: estructura con atributos para la cola  */
			mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
			if(mq==-1){
				perror("[HIJO]: Error en la apertura de la cola");
				exit(-1);
			}

			printf ("[HIJO]: mi PID es %d y mi PPID es %d\n", getpid(), getppid());
			
			// Rellenamos el buffer que vamos a enviar
			// Semilla de los números aleatorios,
			//    establecida a la hora actual
			srand(time(NULL));
			// Número aleatorio entre 0 y 4999
			numeroAleatorio = rand()%5000;
			sprintf(buffer,"%d",numeroAleatorio);

			printf("[HIJO]: genero el mensaje \"%s\"\n", buffer);

			// Mandamos el mensaje
			printf("[HIJO]: enviando mensaje...\n");
			resultado = mq_send(mq, buffer, MAX_SIZE, 0);
			if(resultado == -1){
				perror("[HIJO]: Error al enviar mensaje");
				exit(-1);
			}

			printf("[HIJO]: Mensaje enviado! Salgo...\n");
			// Cerrar la cola
			if(mq_close(mq) == -1){
				perror("[HIJO]: Error cerrando la cola");
				exit(-1);
			}
			break;

		// Padre
		default:

			/* Apertura de la cola */
			mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
			if(mq==-1){
				perror("[PADRE]: Error en la apertura de la cola");
				exit(-1);
			}

			printf ("[PADRE]: mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			printf ("[PADRE]: recibiendo mensaje (espera bloqueante)...\n");

			// Recibimos un mensaje a través de la cola
			resultado = mq_receive(mq, buffer, MAX_SIZE, NULL);
			if(resultado <= 0){
				perror("[PADRE]: Error al recibir el mensaje");
				exit(-1);			
			}
			
			// Imprimimos el mensaje recibido
			printf("[PADRE]: el mensaje recibido es \"%s\"\n", buffer);

			// Cerrar la cola
			if(mq_close(mq) == -1){
				perror("[PADRE]: Error cerrando la cola");
				exit(-1);
			}
			printf("[PADRE]: Cola cerrada.\n");
			died=wait(&status);
			// Eliminar la cola
			if(mq_unlink(QUEUE_NAME) == -1){
				perror("[PADRE]: Error eliminando la cola");
				exit(-1);
			}
			printf("[PADRE]: El proceso hijo con PID %d ha salido con código de error %d. Salgo...\n", died, status);			
	}

	exit(0);
}
