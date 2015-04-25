#include "common.h"

// Apuntador al fichero de log (se utilizará en el ejercicio resumen)
FILE *fLog = NULL;

// flag que indica cuando hay que parar
int must_stop = 0;


void miManejador(int signal){
	printf("Capture la señal\n");
	must_stop=1;
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
	char server[MAX_SIZE];
	char client[MAX_SIZE];

	int option_index = 0;

	// Cola del servidor
	mqd_t mq_server;

	//Cola del cliente
	mqd_t mq_client;
	
	//Para comprobar expresiones regulares
	regex_t regex;

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
		param = "[A-Z]";
	}


	//Concatenamos a los nombres de las colas, nuestros nombres de usuario
	user = getenv("USER");
	strcpy(server, SERVER_QUEUE);
	strcat(server, "-");
	strcat(server, user);
	
	strcpy(client, CLIENT_QUEUE);
	strcat(client, "-");
	strcat(client, user);

	/*Capturamos las posibles señales*/


    if (signal(SIGINT, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGHUP, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGHUP al manejador!\n");
    if (signal(SIGTERM, miManejador) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

	


	// Crear la cola de mensajes del servidor
	mq_server = mq_open(server, O_CREAT | O_RDONLY, 0644, &attr);
	if(mq_server == (mqd_t)-1 ){
        	perror("Error al abrir la cola del servidor");
       		exit(-1);
	}

	//Crear la cola de mensajes del cliente
	mq_client = mq_open(CLIENT_QUEUE, O_WRONLY);
	if(mq_client == (mqd_t)-1){
		perror("Error al abrir la cola del cliente");
		exit(-1);
	}


	do {
		// Número de bytes leidos
		ssize_t bytes_read;

		// Recibir el mensaje
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
		// Comprar que la recepción es correcta (bytes leidos no son negativos)
		if(bytes_read < 0){
			perror("Error al recibir el mensaje");
			exit(-1);
		}

		// Cerrar la cadena
		buffer[bytes_read] = '\0';

		// Comprobar el fin del bucle
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop = 1;
		else
			printf("Recibido el mensaje: %s\n", buffer);


		//Aqui deberemos comprobar las expresiones regulares, para mandarle el mensaje al cliente

		//Comprobamos si ha activado la opcion ERE
		
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
			exit(-1);
		}



	// Iterar hasta que llegue el código de salida
	} while (!must_stop);

	// Cerrar la cola del servidor
	if(mq_close(mq_server) == (mqd_t)-1){
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	// Eliminar la cola del servidor
	if(mq_unlink(SERVER_QUEUE) == (mqd_t)-1){
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}

	regfree(&regex);

	return 0;
}