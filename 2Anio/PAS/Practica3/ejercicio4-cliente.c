#include "common.h"

// Apuntador al fichero de log (se utilizará en el ejercicio resumen)
FILE *fLog = NULL;

void funcionLog(char * mensaje);

int main(int argc, char **argv)
{


	//Nombre de la cola

	char * user;
	char logmsg[MAX_SIZE];
	char server[MAX_SIZE];
	char client[MAX_SIZE];
	
	// Cola del servidor
	mqd_t mq_server;
	//Cola del cliente
	mqd_t mq_client;

	//Para los atributos de la cola
	struct mq_attr attr;

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];
	char bufferRegex[MAX_SIZE];

	//Numero de bytes leidos
	ssize_t bytes_read;

		// Inicializar los atributos de la cola
	
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje
	

	//Le ponemos nombre al servidor
	user = getenv("USER");
	strcpy(server, SERVER_QUEUE);
	strcat(server, "-");
	strcat(server, user);
	
	strcpy(client, CLIENT_QUEUE);
	strcat(client, "-");
	strcat(client, user);


	//Abrimos la cola del cliente
	mq_client = mq_open(client, O_RDONLY, 0644, &attr);
	if(mq_client == (mqd_t)-1){
		perror("Error al abrir la cola del cliente");
		funcionLog("Error al abrir la cola del cliente");
		exit(-1);
	}



	// Abrir la cola del servidor
	mq_server = mq_open(server, O_WRONLY);
	if(mq_server == (mqd_t)-1 ){
        	perror("Error al abrir la cola del servidor");
        	funcionLog("Error al abrir la cola del servidor");
       		exit(-1);
	}

	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
	funcionLog("Mandando mensajes al servidor");

	do {
		printf("> ");
		fflush(stdout);                  // Limpiar buffer de salida

		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer
		fgets(buffer, MAX_SIZE, stdin);  // Leer por teclado
		buffer[strlen(buffer)-1] = '\0'; // Descartar el salto de línea

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0){
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje");
			exit(-1);
		}

		sprintf(logmsg, "Mensaje enviado: %s", buffer);
		funcionLog(logmsg);


		//Y recibimos el mensaje del servidor del emparejamiento


		// Recibir el mensaje
		bytes_read = mq_receive(mq_client, bufferRegex, MAX_SIZE, NULL);
		// Comprar que la recepción es correcta (bytes leidos no son negativos)
		if(bytes_read < 0){
			perror("Error al recibir el mensaje");
			funcionLog("Error al recibir el mensaje del servidor");
			exit(-1);
		}else{
			//Si el mensaje recibido es exit, no lo mostramos
			if(strncmp(bufferRegex, MSG_STOP, strlen(MSG_STOP))){
				printf("El mensaje: %s\n", bufferRegex);
				sprintf(logmsg, "Mensaje recibido: %s", bufferRegex);
				funcionLog(logmsg);
			}
		}



	// Iterar hasta escribir el código de salida
	} while (strncmp(bufferRegex, MSG_STOP, strlen(MSG_STOP)));

	funcionLog("Cerramos las colas");

	// Cerrar la cola del servidor
	if(mq_close(mq_server) == (mqd_t)-1){
		perror("Error al cerrar la cola del servidor");
		funcionLog("Error al cerrar la cola del servidor");
		exit(-1);
	}

	//Cerrar la cola del cliente
	if(mq_close(mq_client) == (mqd_t)-1){
		perror("Error al cerrar la cola del cliente");
		funcionLog("Error al cerrar la cola del cliente");
		exit(-1);
	}

	return 0;
}



// Función auxiliar, escritura de un log
void funcionLog(char *mensaje) {
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero,"log-cliente.txt");
	if(fLog==NULL){
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL){
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);
	
	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir,fLog);
	if ( resultado < 0)
		perror("Error escribiendo en el fichero de log");

	fclose(fLog);
	fLog=NULL;
}


#include "common.h"