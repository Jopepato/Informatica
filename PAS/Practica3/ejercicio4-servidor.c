#include "common.h"

// Apuntador al fichero de log (se utilizará en el ejercicio resumen)
FILE *fLog = NULL;

// Cola del servidor
mqd_t mq_server;

//Cola del cliente
mqd_t mq_client;

char server[MAX_SIZE];
char client[MAX_SIZE];
char logmsg[MAX_SIZE];


//Para comprobar expresiones regulares
regex_t regex;

void funcionLog(char *mensaje);

void miManejador(int signal){
	
	printf("Capture la señal\n");
	funcionLog("Hemos capturado una señal y procedemos a cerrar ambos programas");
	char mensaje[MAX_SIZE +1];
	//Mandamos una señal al cliente para que pare y a su vez este mandara una al servidor

	//Le enviamos la señal de stop al cliente y cerramos las colas de aqui
	strcpy(mensaje, "exit\0");

	if(mq_send(mq_client, mensaje, MAX_SIZE, 0) != 0){

		perror("Error al enviar el mensaje");
		funcionLog("Error al enviar el mensaje");
		exit(-1);
	}

	funcionLog("Cerramos y borramos las colas");

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

	// Eliminar la cola del servidor
	if(mq_unlink(server) == (mqd_t)-1){
		perror("Error al eliminar la cola del servidor");
		funcionLog("Error al eliminar la cola del servidor");
		exit(-1);
	}

	//Eliminar la cola del cliente
	if(mq_unlink(client) == (mqd_t)-1){
		perror("Error al eliminar la cola del cliente");
		funcionLog("Error al eliminar la cola del cliente");
		exit(-1);
	}


	funcionLog("Colas cerradas y eliminadas");

	regfree(&regex);
	funcionLog("Liberamos el regex");

	funcionLog("Cerramos ficheros");
	//Comprobamos si el fichero esta apuntando a NULL, es que ya esta cerrado debido a la funcion
	if(fLog!=NULL){
		fclose(fLog);
		fLog = NULL;
	}
	printf("Todo cerrado\n");

	exit(0);

}


void imprimirAyuda(){
	printf("Uso del programa: ejercicio4-servidor [opciones]\n");
	printf("-h, --help \t Imprimir esta ayuda\n");
	printf("-r, --regex=EXPR \t Expresion regular a utilizar\n");
	printf("-e, --ere \t Utilizar expresiones regulares de tipo ERE\n");
}


int main(int argc, char **argv)
{


	int c;
	/* Estructura a utilizar por getoptlong */
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"regex",	 required_argument,	   0, 'r'},
		{"ere",  no_argument,	   0, 'e'},
		{"help",  no_argument, 0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};
	//Declaramos las banderas
	int rflag = 0;
	int eflag = 0;
	char * param;
	char * user;

	int option_index = 0;

	// flag que indica cuando hay que parar
	int must_stop = 0;
	
	// Atributos de la cola
	struct mq_attr attr;

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE + 1];
	char bufferRegex[MAX_SIZE+1];	

	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje


	//Para comprobar las opciones introducidas
	while ((c = getopt_long (argc, argv, "ehr:", long_options, &option_index))!=-1)
	{

		if (c == -1)
			break;

		switch (c)
		{

		case 'r':
			rflag=1;
			param = optarg;
			break;

		case 'e':
			
			eflag = 1;
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
	/*Con esto ya tenemos las opciones introducidas por el usuario al lanzar el servidor*/

	if(rflag==0){
		//No se ha especificado ninguna expresion regular
		param = "[A-Z]\0";
	}


	//Concatenamos a los nombres de las colas, nuestros nombres de usuario
	user = getenv("USER");
	strcpy(server, SERVER_QUEUE);
	strcat(server, "-");
	strcat(server, user);
	
	strcpy(client, CLIENT_QUEUE);
	strcat(client, "-");
	strcat(client, user);
	

	// Crear la cola de mensajes del servidor
	mq_server = mq_open(server, O_CREAT | O_RDONLY, 0644, &attr);
	if(mq_server == (mqd_t)-1 ){
        	perror("Error al abrir la cola del servidor");
        	funcionLog("Error al abrir la cola del servidor");
       		exit(-1);
	}

	//Crear la cola de mensajes del cliente
	mq_client = mq_open(client, O_CREAT | O_WRONLY, 0644, &attr);
	if(mq_client == (mqd_t)-1){
		perror("Error al abrir la cola del cliente");
		funcionLog("Error al abrir la cola del cliente");
		exit(-1);
	}





	do {

		/*Captura de las posibles señales*/
		if (signal(SIGINT, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    	if (signal(SIGHUP, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGHUP al manejador!\n");
    	if (signal(SIGTERM, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

		// Número de bytes leidos
		ssize_t bytes_read;

		// Recibir el mensaje
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
		// Comprar que la recepción es correcta (bytes leidos no son negativos)
		if(bytes_read < 0){
			perror("Error al recibir el mensaje");
			funcionLog("Error al recibir el mensaje");
			exit(-1);
		}

		// Cerrar la cadena
		buffer[bytes_read] = '\0';

		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0){
			must_stop = 1;
			//Enviamos de vuelta el mensaje de exit
			if(mq_send(mq_client, buffer, MAX_SIZE, 0) != 0){
				perror("Error al enviar el mensaje");
				funcionLog("Error al enviar el mensaje");
				exit(-1);
			}else{
				sprintf(logmsg, "Mensaje enviado: %s", buffer);
				funcionLog(logmsg);
			}

		}
		else{
			printf("Recibido el mensaje: %s\n", buffer);
			sprintf(logmsg, "Recibido el mensaje: %s", buffer);
			funcionLog(logmsg);




		//Aqui deberemos comprobar las expresiones regulares, para mandarle el mensaje al cliente

		//Comprobamos si ha activado la opcion ERE

		//Comprobamos si hemos recibido el mensaje de exit, para enviarselo de vuelta al servidor
		
		if(eflag==1){
					if(regcomp(&regex, param, REG_EXTENDED)){
						perror("Regex error");
						exit(-1);
					}else{
						if (regexec(&regex, buffer, (size_t)0, NULL, 0))
						{
						strcpy(bufferRegex, "No empareja");
						}else{
						strcpy(bufferRegex, "Empareja");
						}
					}

		}else{
					if(regcomp(&regex,param,0)){
						perror("Regex error");
						exit(-1);
					}else{
						if (regexec(&regex, buffer, (size_t)0, NULL, 0))
						{
						strcpy(bufferRegex, "No empareja");
						}else{
						strcpy(bufferRegex, "Empareja");
						}

					}
				}

		//Ahora enviamos el mensaje a la cola del cliente
		if(mq_send(mq_client, bufferRegex, MAX_SIZE, 0) != 0){
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje");
			exit(-1);
		}else{
			sprintf(logmsg, "Mensaje enviado: %s", bufferRegex);
			funcionLog(logmsg);
		}

	}

	// Iterar hasta que llegue el código de salida
	} while (!must_stop);


	funcionLog("Cerramos y borramos las colas");

	// Cerrar la cola del servidor
	if(mq_close(mq_server) == (mqd_t)-1){
		perror("Error al cerrar la cola del servidor");
		funcionLog("Error al cerrar la cola del servidor");
		exit(-1);
	}

	// Eliminar la cola del servidor
	if(mq_unlink(server) == (mqd_t)-1){
		perror("Error al eliminar la cola del servidor");
		funcionLog("Error al eliminar la cola del servidor");
		exit(-1);
	}


	//Cerrar la cola del cliente
	if(mq_close(mq_client) == (mqd_t)-1){
		perror("Error al cerrar la cola del cliente");
		funcionLog("Error al cerrar la cola del cliente");
		exit(-1);
	}

	//Eliminar la cola del cliente
	if(mq_unlink(client) == (mqd_t)-1){
		perror("Error al eliminar la cola del cliente");
		funcionLog("Error al eliminar la cola del cliente");
		exit(-1);
	}

	funcionLog("Colas cerradas y eliminadas");

	regfree(&regex);
	funcionLog("Liberamos el regex");

	return 0;
}





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