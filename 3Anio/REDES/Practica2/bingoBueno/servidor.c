#include "funciones.h"



void manejador(int signum);



int main ()
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	char buffer2[MSG_SIZE];
    char bufferBolas[MSG_SIZE];
    char bufferPartidas[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    struct cliente arrayClientes[MAX_CLIENTES];
    struct partida arrayPartidas[MAX_PARTIDAS];
    int numClientes = 0;
    int numPartidas = 0;
    char * opcion;
    char aux[MSG_SIZE];
    char * aux2;
    char usuario[50];
    char password[50];
    char bufferCarton[MSG_SIZE];
    char bufferSalir[MSG_SIZE];
    int comprueba;
    //contadores
    int i,j,k, w, x, y, z;
	int recibidos;
    int cuentaPartidas;
    char identificador[MSG_SIZE];
    struct timeval timeout;
    int mandabola;
    int on, ret;
    int posicion;
    int bola;
    int posicionPartida;
    int posicionAux;
    
    estadoPartidasA0(arrayPartidas);
    //Inicializamos el tiempo a null
    srand(time(NULL));
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
                                    printf("Cliente %d conectado\n", new_sd);
                                
                                    
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
                             
                                    salirServidor(arrayClientes, sd, numClientes, &readfds);
                                    exit(-1);
                                
                                
                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{
                            //Lo que hemos recibido es por el teclado de los clientes
                            bzero(buffer,sizeof(buffer));
                            
                            recibidos = recv(i,buffer,sizeof(buffer),0);

                            //Pillamos la posicion del cliente en el array
                            posicion = devuelvePosicion(arrayClientes, i, numClientes);
                            
                            if(recibidos > 0){//Han introducido algo por teclado

                            	strcpy(buffer2, buffer);
                            	opcion = strtok(buffer2, " ");
                            	//Aqui miramos todas las opciones para ver que hacer
                                
                                if(strcmp(buffer,"SALIR\n") == 0){
                                	//Opcion SALIR
                                    if(arrayClientes[posicion].estado<=2){
                                        //No esta en partida ni buscando una
                                        salirCliente(i,&readfds,&numClientes,arrayClientes);
                                        printf("El cliente %d se fue\n", i);
                                        numClientes--;
                                        fflush(stdout);
                                    }else{
                                        //Esta en partida o buscando una
                                        send(i, "-ERR, para salir, primer debes de salir de partida\n", strlen("-ERR, para salir, primer debes de salir de partida\n"), 0);
                                    }

                                //Cierre if SALIR
                                }else if(strcmp(opcion, "REGISTER")==0){
                                	//-u USUARIO -p PASSWORD
                                	strncpy(aux, buffer+strlen(opcion)+4, 100);
                                	aux2 = strtok(aux, " ");
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
                                        printf("Usuario registrado %s y password %s\n", usuario, password);
                                        fflush(stdout);
                                	}else{
                                		//Ha salido mal
                                		send(i, "-ERR, usuario ya existente\n", strlen("-ERR, usuario ya existente\n"),0 );
                                        printf("Intento de registro de usuario %s, pero ya existente", usuario);
                                        fflush(stdout);
                                	}
                                //Cierre if register
                                }else if(strcmp(opcion, "USUARIO")==0){
                                	//OPCION USUARIO
                                	if(arrayClientes[posicion].estado==0){
                                        //Podemos ver si el usuario es correcto
                                        //Ahora pillamos lo que ha puesto por teclado
                                        strncpy(aux, buffer+strlen(opcion)+1, 50);
                                        aux2 = strtok(aux, "\n");
                                        strcpy(usuario, aux2);
                                        //con esto tenemos el nombre en aux2
                                        if(compruebaUsuario(usuario)==1){
                                            arrayClientes[posicion].estado = 1;
                                            strcpy(arrayClientes[posicion].usuario, usuario);
                                            send(i, "+Ok, usuario correcto\n", strlen("+Ok, usuario correcto\n"),0 );
                                        }else{
                                            send(i, "-ERR, usuario no existente\n", strlen("-ERR, usuario no existente\n"),0 );
                                        }
                                    }else{
                                        //A este usuario no le corresponde este estado
                                        send(i, "-ERR, ya has introducido nombre de usuario\n", strlen("-ERR, ya has introducido nombre de usuario\n"), 0);
                                    }
                                //Cierre if USUARIO
                                }else if(strcmp(opcion, "PASSWORD")==0){
                                	//OPCION PASSWORD
                                    if(arrayClientes[posicion].estado==1){
                                        //Puede pedir esto, puesto que ya ha introducido el usuario
                                        strncpy(aux, buffer+strlen(opcion)+1, 50);
                                        aux2 = strtok(aux, "\n");
                                        strcpy(password, aux2);
                                        if(compruebaUsuarioPassword(arrayClientes[posicion].usuario, password)==1){
                                            //Password introducido correcto
                                            arrayClientes[posicion].estado = 2;
                                            strcpy(arrayClientes[posicion].password, password);
                                            //Mandamos que todo correcto
                                            send(i, "+Ok, password correcto\n", strlen("+Ok, password correcto\n"),0 );
                                        }else{
                                            //Password no coincide con usuario
                                            send(i, "-ERR, password incorrecto\n", strlen("-ERR, password incorrecto\n"),0 );
                                        }
                                    }else{
                                        //Aun no se ha logeado como usuario
                                	       send(i, "Primero introduce el usuario\n", strlen("Primero introduce el usuario\n"), 0);
                                    }
                                //Cierre if password
                                }else if(strcmp(buffer, "INICIAR-PARTIDA\n")==0){
                                    //Primero miramos que el estado de cliente debe ser correcto
                                    if(arrayClientes[posicion].estado==2){
                                        if(numPartidas>10){
                                            send(i, "-ERR, espere unos minutos\n", strlen("-ERR, espere unos minutos\n"), 0);
                                            //Y te sales del bucle
                                        }else{
                                       	   for(cuentaPartidas=0; cuentaPartidas<10; cuentaPartidas++){
                                                //Pilla la primera partida libre
                                                if(arrayPartidas[cuentaPartidas].estado==0){
                                                    //Ahora miramos que hay menos de cuatro jugadores esperando
                                                    if(arrayPartidas[cuentaPartidas].numClientes < 3){
                                                        //Añadimos uno al numero de clientes
                                                        arrayClientes[posicion].estado=3;
                                                        arrayPartidas[cuentaPartidas].clientes[arrayPartidas[cuentaPartidas].numClientes] = arrayClientes[posicion];
                                                        arrayPartidas[cuentaPartidas].numClientes+=1;
                                                        send(i, "+Ok, esperando partida\n", strlen("+Ok, esperando partida\n"), 0);
                                                        //Y se sale del bucle
                                                        break;
                                                    }
                                                    if(arrayPartidas[cuentaPartidas].numClientes == 3){
                                                        //Se esta listo para iniciar la partida
                                                        arrayClientes[posicion].estado=4;
                                                        arrayPartidas[cuentaPartidas].clientes[arrayPartidas[cuentaPartidas].numClientes] = arrayClientes[posicion];
                                                        arrayPartidas[cuentaPartidas].numClientes+=1;
                                                        //Aumentamos el numero de partidas
                                                        numPartidas++;
                                                        //Iniciamos la partida
                                                        //Mandariamos a todos los de la partida que empieza la partida
                                                        for(w=0; w<=arrayPartidas[cuentaPartidas].numClientes; w++){
                                                            //Rellenamos los cartones de los jugadores y se los mandamos
                                                            arrayPartidas[cuentaPartidas].clientes[w].estado=4;
                                                            posicionAux= devuelvePosicion(arrayClientes, arrayPartidas[cuentaPartidas].clientes[w].descriptor, numClientes);
                                                            arrayClientes[posicionAux].estado=4;
                                                            arrayPartidas[cuentaPartidas].clientes[w].carton = generaCarton();
                                                            //Pasamos el carton a un buffer
                                                            cartonABuffer(bufferCarton, arrayPartidas[cuentaPartidas].clientes[w].carton);
                                                            send(arrayPartidas[cuentaPartidas].clientes[w].descriptor, "+Ok, empieza la partida\n", strlen("+Ok, empieza la partida\n"), 0);
                                                            //Y mandamos de paso el carton
                                                            usleep(5);
                                                            send(arrayPartidas[cuentaPartidas].clientes[w].descriptor, bufferCarton, strlen(bufferCarton), 0);
                                                            bzero(bufferCarton, sizeof(bufferCarton));
                                                            //Ponemos los estados de los jugadores a 4
                                                            arrayPartidas[cuentaPartidas].clientes[w].estado=4;
                                                            posicionAux= devuelvePosicion(arrayClientes, arrayPartidas[cuentaPartidas].clientes[w].descriptor, numClientes);
                                                            arrayClientes[posicionAux].estado=4;
                                                        }
                                                        //Y se sale del bucle
                                                        printf("Inicio de la partida %d\n", cuentaPartidas);
                                                        fflush(stdout);
                                                        arrayPartidas[cuentaPartidas].estado = 1;
                                                        break;
                                                    }//Cierre if numClientes==3
                                                }//Cierre if partida.estado==0
                                            }//Cierre for partidas
                                        }//Cierre else
                                    }else{
                                        send(i, "-ERR, no puedes pedir partida aun\n", strlen("-ERR, no puedes pedir partida aun\n"), 0);
                                    }
                                    //Cierre if iniciar-partida
                                }else if(strcmp(buffer, "UNA-LINEA\n")==0){
                                    if(arrayClientes[posicion].estado==4){
                                        printf("Intentan cantar linea\n");
                                        fflush(stdout);
                                        //Esta en partida asi que puede hacer esto
                                        //Comprobamos su carton y las bolas de la partida para ver si tiene linea
                                        posicionPartida = getPartida(arrayPartidas, arrayClientes[posicion].descriptor);
                                        //Comprobamos que no han cantado linea antes
                                        if(arrayPartidas[posicionPartida].estado==1){
                                            //Comprobamos que es linea
                                            if(compruebaLinea(arrayPartidas[posicionPartida].clientes[w].carton, arrayPartidas[posicionPartida].bolas, arrayPartidas[posicionPartida].numBolas)){
                                                //La linea es correcta actualizamos el estado de la partida y avisamos a todos los jugadores
                                                arrayPartidas[posicionPartida].estado = 2;
                                                //Se lo decimos a los demas jugadores
                                                for(z=0; z<arrayPartidas[posicionPartida].numClientes; z++){
                                                    //Al que ha cantado linea le decimos otra cosa
                                                    if(arrayPartidas[posicionPartida].clientes[z].descriptor!=i){
                                                        //Los jugadores que no han cantado linea
                                                        bzero(bufferPartidas, sizeof(bufferPartidas));
                                                        sprintf(bufferPartidas, "+Ok, el jugador %s ha cantado linea\n", arrayPartidas[posicionPartida].clientes[z].usuario);
                                                        send(arrayPartidas[posicionPartida].clientes[z].descriptor, bufferPartidas, strlen(bufferPartidas), 0);
                                                    }else{
                                                        //El que ha cantado linea
                                                        send(i, "+Ok, enhorabuena has cantado linea\n", strlen("+Ok, enhorabuena has cantado linea\n"), 0);
                                                    }//Cierre for envio de mensajes
                                                }
                                            //Cierre if comprueba-linea
                                            }else{
                                                //La linea es correcta
                                                printf("Linea incorrecta en partida %d", posicionPartida);
                                                fflush(stdout);
                                                send(i, "-ERR, su carton no contiene linea\n", strlen("-ERR, su carton no contiene linea\n"), 0);
                                            }//Cierre else comprueba linea
                                        //Cierre if estadoPartida==1
                                        }else{
                                            send(i, "-ERR, ya han cantado linea\n", strlen("-ERR, ya han cantado linea\n"), 0);
                                        }
                                    //Cierre if estadoJugador==4
                                    }else{
                                        //Aun no esta en partida, no puede usar este comando
                                        send(i, "-ERR, no estas en partida aun\n", strlen("-ERR, no estas en partida aun\n"), 0);
                                    }

                                    //Cierre if una-linea
                                }else if(strcmp(buffer, "DOS-LINEAS\n")==0){

                                    //Cierre if dos-lineas
                                }else if(strcmp(buffer, "BINGO\n")==0){

                                    //Cierre if bingo
                                }else if(strcmp(buffer, "SALIR-PARTIDA\n")==0){
                                    //A ver como se da
                                    if(arrayClientes[posicion].estado>2){
                                        //Esta en partida asi que puede hacer el salir-partida
                                        posicionPartida = getPartida(arrayPartidas, i);
                                        salirPartida(i, posicionPartida, arrayPartidas);
                                        printf("El cliente %d ha hecho un salir Partida\n", i);
                                        fflush(stdout);
                                        send(i, "+Ok, has salido de partida\n", strlen("+Ok, has salido de partida\n"), 0);
                                        
                                        if(arrayClientes[posicion].estado==4){
                                            //Estaba en partida a si que avisamos a sus compañeros de que un cliente ha abandonado la partida
                                            bzero(bufferSalir, sizeof(bufferSalir));
                                            sprintf(bufferSalir, "El cliente %s ha abandonado la partida\n", arrayClientes[posicion].usuario);
                                            for(k=0; k<arrayPartidas[posicionPartida].numClientes;k++){
                                                send(arrayPartidas[posicionPartida].clientes[k].descriptor, bufferSalir, strlen(bufferSalir), 0);
                                            }
                                        }
                                        //Comprobamos si todos han abandonado la partida
                                        if(arrayPartidas[posicionPartida].numClientes==0){
                                            numPartidas--;
                                        }
                                        //Y le volvemos a poner el estado 2
                                        arrayClientes[posicion].estado=2;
                                    //Cierre if estado>2
                                    }else{
                                        //No esta en partida
                                        send(i, "-ERR, no estas en partida\n", strlen("-ERR, no estas en partida\n"), 0);
                                    }

                                    //Cierre if salir-partida
                                }else{
                                    //Opcion no valida
                                    send(i, "-ERR\n", strlen("-ERR\n"), 0);
                                }
                                                                
                                
                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0){

                                salirCliente(i,&readfds,&numClientes,arrayClientes);
                                printf("El cliente %d se fue\n", i);
                                fflush(stdout);
                            }//Cierre if de recibidos==0
                            
                        }
                    }
                }
            }//Cierre del if (salida>0)
            else{
                if(salida==0){
                    bzero(bufferBolas, sizeof(bufferBolas));
                    timeout.tv_sec = 5;
                    timeout.tv_usec = 0;
                    //Valo esta esta preparado para las bolas
                    //Esto es que se ha agotado el tiempo del servidor
                    //Vamos a mandar mensaje a todos los clientes
                    //Recorremos el vector de clientes que tenemos y vamos mandando a su descriptor
                    if(numPartidas>0){
                        //Hay partidas activas, asi que las tenemos que ir recorriendo y mandar bolas
                        for(x=0; x<10; x++){
                            if(arrayPartidas[x].estado>0){
                                //Se mandan bolas a esta partida
                                if(arrayPartidas[x].numBolas < 90){
                                    //Mandamos la bola
                                    bola = getBola(arrayPartidas[x].bolas);
                                    arrayPartidas[x].bolas[arrayPartidas[x].numBolas] = bola;
                                    arrayPartidas[x].numBolas++;
                                    //Y mandamos la bola
                                    sprintf(bufferBolas,"NUMERO OBTENIDO: %d",bola);
                                    //Y ahora tenemos que mandarlo a los clientes de las partidas
                                    for(y=0; y<arrayPartidas[x].numClientes; y++){
                                        send(arrayPartidas[x].clientes[y].descriptor, bufferBolas, strlen(bufferBolas), 0);
                                    }
                                    bzero(bufferBolas, sizeof(bufferBolas));
                                }//Cierre if estado
                            }
                        }//Cierre for
                    }//Cierre if numPartidas
                }//Cierre if salida==0
            }
		}

		close(sd);
	
    return 1;
}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}