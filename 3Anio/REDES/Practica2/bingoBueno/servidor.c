#include "funciones.h"



void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]);




void main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	char buffer2[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    struct cliente arrayClientes[MAX_CLIENTES];
    int numClientes = 0;
    char * opcion;
    char aux[MSG_SIZE];
    char * aux2;
    char usuario[50];
    char password[50];
    int comprueba;
    //contadores
    int i,j,k;
	int recibidos;
    char identificador[MSG_SIZE];
    struct timeval timeout;
    int mandabola;
    int on, ret;

    
    
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}
    printf("%d\n", sd);
    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

    //Asocia el socket con el puerto
	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
	

   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}
    
    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);
    
   	
    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){
            
            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
            
            auxfds = readfds;
            
            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,&timeout);
            
            if(salida > 0){
                //Ha pasado algo en el selecte de que ha leido algo
                
                for(i=0; i<FD_SETSIZE; i++){
                    
                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {
                        
                        if(i == sd){
                            
                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else
                            {
                                if(numClientes < MAX_CLIENTES){
                                    //Metemos al nuevo cliente en el array
                                    arrayClientes[numClientes].descriptor = new_sd;
                                    arrayClientes[numClientes].estado = 0;
                                    numClientes++;
                                    FD_SET(new_sd, &readfds);
                                	bzero(buffer,sizeof(buffer));

                                    sprintf(buffer, "Bienvenido al bingo, tu descriptor es: %d\n", new_sd);

                                    send(new_sd,buffer,strlen(buffer),0);
                                
                                    
                                }//Cierre if de aceptacion clientes
                                else{
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    send(new_sd,buffer,strlen(buffer),0);
                                    close(new_sd);
                                }
                                
                            }
                            
                            
                        }
                        //La lectura 
                        else if (i == 0){
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
                            
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){
                             
                                for (j = 0; j < numClientes; j++){
                                    send(arrayClientes[j].descriptor, "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                                    close(arrayClientes[j].descriptor);
                                    FD_CLR(arrayClientes[j].descriptor,&readfds);
                                }
                                    close(sd);
                                    exit(-1);
                                
                                
                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{
                            //Lo que hemos recibido es por el teclado de los clientes
                            bzero(buffer,sizeof(buffer));
                            
                            recibidos = recv(i,buffer,sizeof(buffer),0);
                            
                            if(recibidos > 0){//Han introducido algo por teclado

                            	strcpy(buffer2, buffer);
                            	opcion = strtok(buffer2, " ");
                            	//Aqui miramos todas las opciones para ver que hacer
                                
                                if(strcmp(opcion,"SALIR") == 0){
                                	//Opcion SALIR
                                    
                                    //salirCliente(i,&readfds,&numClientes,arrayClientes);

                                //Cierre if SALIR
                                }else if(strcmp(opcion, "REGISTER")==0){
                                	//-u USUARIO -p PASSWORD
                                	strncpy(aux, buffer+strlen(opcion)+4, 100);
                                	aux2 = strtok(aux, " ");
                                	fflush(stdout);
                                	//Ya tenemos el nombre del usuario
                                	strcpy(usuario, aux2);
                                	//Ahora cogemos la contraseña
                                	bzero(aux, sizeof(aux));
                                	strncpy(aux, buffer+strlen(opcion)+4+strlen(usuario)+4, 512);
                                	aux2 = strtok(aux, "\n");
                                	strcpy(password, aux2);
                                	if(registroUsuario(usuario, password)==1){
                                		//Ha salido bien
                                		send(i, "+Ok, usuario registrado\n", strlen("+Ok, usuario registrado\n"),0 );
                                	}else{
                                		//Ha salido mal
                                		send(i, "-ERR, usuario ya existente\n", strlen("-ERR, usuario ya existente\n"),0 );
                                	}
                                //Cierre if register
                                }else if(strcmp(opcion, "USUARIO")==0){
                                	//OPCION USUARIO
                                	send(i, "Holi\n", sizeof("Holi\n"), 0);
                                //Cierre if USUARIO
                                }else if(strcmp(opcion, "PASSWORD")==0){
                                	//OPCION PASSWORD
                                	send(i, "Holo\n", sizeof("Holo\n"), 0);
                                //Cierre if password
                                }else{
                                	send(i, "Cosa rara\n", strlen("Cosa rara\n"), 0);
                                }
                                                                
                                
                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0){
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
                                //salirCliente(i,&readfds,&numClientes,arrayClientes);
                                break;
                            }//Cierre if de recibidos==0
                        }
                    }
                }
            }//Cierre del if (salida>0)
            else{
                if(salida==0){
                    timeout.tv_sec = 5;
                    timeout.tv_usec = 0;
                    //Valo esta esta preparado para las bolas
                    //Esto es que se ha agotado el tiempo del servidor
                    //Vamos a mandar mensaje a todos los clientes
                    //Recorremos el vector de clientes que tenemos y vamos mandando a su descriptor
                    for(mandabola=0; mandabola<numClientes; mandabola++){
                        send(arrayClientes[mandabola].descriptor, "Tiempo Agotado\n", sizeof("Tiempo Agotado\n"), 0);
                    }
                    printf("Tiempo agotado\n");
                    fflush(stdout);
                }
            }
		}

		close(sd);
	
}


void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]){
  
    char buffer[250];
    int j;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j+1]);
    
    (*numClientes)--;
    
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);
    
    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j] != socket)
            send(arrayClientes[j],buffer,strlen(buffer),0);


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}