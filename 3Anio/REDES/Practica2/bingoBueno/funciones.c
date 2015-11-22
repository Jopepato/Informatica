#include "funciones.h"

int compruebaElementoVector(int * vector, int elem, int nelem){
int i=0;
	for(i=0; i<nelem; i++){
		if(vector[i]==elem){
			return 1;
		}
	}

	return 0;

}

int compruebaElementoMatriz(int ** matriz, int elem){
	//Con esta funcion comprobamos si el elemento esta en la matriz
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(matriz[i][j] == elem){
				return 1;
			}
		}
	}
	
return 0;

}

int ** generaCarton(){
	int ** carton;
	int i,j,k=0;
	int aux;
	int quita;
	int quitados[4];
	//reservamos memoria
	
	carton = (int **)malloc(3*sizeof(int*));
	for(i=0; i<3; i++){
		carton[i] = (int*)malloc(9*sizeof(int));
	}

	//Rellenamos el carton con ceros
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			carton[i][j]=0;
		}
	}
	
	//Hacemos las bolas aleatorias para el carton

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			aux = (rand()%10) +j*10;
			if(j==8){
				aux = (rand()%11) +j*10;
			}
			if(aux==0){
				while(aux==0){
					aux=rand()%10;
				}
			}
			if(!compruebaElementoMatriz(carton, aux)){
				carton[i][j] = aux;
			}else{
				j--;
			}
		}
	}
	//Rellenamos el vector de quitados con 10
	for(i=0; i<4; i++){
		quitados[i] = 10;
	}

	//Ahora deberemos quitar 4 numeros por fila
	for(i=0; i<3;i++){
		while(k!=4){
			quita = rand()%9;
			if(!compruebaElementoVector(quitados, quita, 4)){
				quitados[k] = quita;
				k++;
				carton[i][quita] = 0;
			}
		}
		for(j=0; j<4; j++){
		quitados[i] = 10;
		}
		k=0;
	}
	
	return carton;
}


void muestraCarton(int ** carton){
	int i,j;

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(carton[i][j]==0){
				printf("X\t");
			}else{
			printf("%d\t", carton[i][j]);
			}
		}
		printf("\n");
	}

}

void salirServidor(struct cliente arrayClientes[], int sd, int numClientes, fd_set * readfds){
	//Para el cierre del servidor
    int j;
    for (j = 0; j < numClientes; j++){
        send(arrayClientes[j].descriptor, "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
        close(arrayClientes[j].descriptor);
        FD_CLR(arrayClientes[j].descriptor, readfds);
    }
    close(sd);	
}


int registroUsuario(char usuario[50], char password[50]){
	FILE * fichero;
	char buffer[512];
	char cadena[120];
	int valido=1;

	valido = compruebaUsuario(usuario);

	//Ahora si valido sigue estando a 1, escribimos
	if(valido==0){
		//Escribimos en el fichero
		fichero = fopen("usuarios.txt", "a");
		strcpy(cadena, usuario);
		strcat(cadena, " ");
		strcat(cadena, password);
		fputs(cadena, fichero);
		fputs("\n", fichero);
		//Cerramos fichero
		fclose(fichero);
		return 1;

	}else{
		//Devolvemos 0
		return 0;
	}

}

int compruebaUsuario(char usuario[50]){
	FILE * fichero;
	char buffer[512];
	int vuelta=0;
	char * usu;

	fichero = fopen("usuarios.txt", "r");

	while((fgets(buffer,512,fichero))!=NULL){
		usu = strtok(buffer, " ");
		if(strcmp(usu, usuario)==0){
			vuelta=1;// El usuario ya existe en el fichero	
		}
	}
	fclose(fichero);

	return vuelta;
}

int compruebaUsuarioPassword(char usuario[50], char password[50]){
	FILE * fichero;
	char buffer[512];
	int vuelta=0;
	char * usu;
	char * pass;
	char aux[50];

	fichero = fopen("usuarios.txt", "r");

	while((fgets(buffer, 512, fichero))!=NULL){
		usu = strtok(buffer, " ");

		if(strcmp(usu, usuario)==0){
			//Comprobamos la contraseña
			strncpy(aux, buffer+strlen(usu)+1, 50);
			
			pass = strtok(aux, "\n");
			//Y ahora comparamos la pass dada con la de ese usuario
			if(strcmp(pass, password)==0){
				vuelta=1;
			}

		}

	}

	fclose(fichero);

	return vuelta;
}

//Devuelve la posicion en la que se encuentra el cliente segundo el descriptor dado
int devuelvePosicion(struct cliente arrayClientes[MAX_CLIENTES], int descriptor, int numClientes){

	//Recorremos el array, buscando 
	int i;

	for(i=0; i<numClientes; i++){
		if(arrayClientes[i].descriptor == descriptor){
			return i;
		}
	}

	return -1;
}

void estadoPartidasA0(struct partida arrayPartidas[10]){
	int i, j;
	for(i=0; i<10; i++){
		arrayPartidas[i].estado=0;
		arrayPartidas[i].numClientes=0;
		arrayPartidas[i].numBolas=0;
		//Llenamos el array de bolas a 0
		for(j=0; j<90; j++){
			arrayPartidas[i].bolas[j]=0;
		}
	}
}

int getBola(int arrayBolas[]){
	//Devuelve una bola
	int bola=0;
	int salir=0;

	while(bola==0 || salir==0){
		bola = rand()%91;
		if(!compruebaElementoVector(arrayBolas, bola, 90)){
			salir =1;
		}
	}

	return bola;
}

int getPartida(struct partida arrayPartidas[], int descriptor){
	//Lo que haremos será recorrer el array de partidas buscando a nuestro cliente
	int i, j;

	for(i=0; i<10; i++){

		//Y tenemos que buscar dentro de las partidas
		for(j=0; j<4; j++){
			if(arrayPartidas[i].clientes[j].descriptor==descriptor){
				return i;
			}
		}
	}

	return -1;
}

int compruebaLinea(int ** carton, int bolas[], int numBolas){
	int i,j;
	int contador=0;
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			
			if(compruebaElementoVector(bolas, carton[i][j], numBolas)){
				contador++;
			}
		}
		if(contador==5){
			return 1;
		}
		contador=0;
	}

	return 0;
}

int compruebaDosLineas(int ** carton, int bolas[], int numBolas){
	int i,j;
	int contador=0, contadorLineas=0;

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(compruebaElementoVector(bolas, carton[i][j], numBolas)){
				contador++;
			}
		}
		if(contador==5){
			contadorLineas++;
		}
		contador=0;
	}

	if(contadorLineas==2){
		return 1;
	}else{
		return 0;
	}
}

int compruebaBingo(int ** carton, int bolas[], int numBolas){
	int i,j;
	int contador=0, contadorLineas=0;

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(compruebaElementoVector(bolas, carton[i][j], numBolas)){
				contador++;
			}
		}
		if(contador==5){
			contadorLineas++;
		}
		contador=0;
	}

	if(contadorLineas==3){
		return 1; //BINGO
	}else{
		return 0;
	}
}

void salirCliente(int socket, fd_set * readfds, int * numClientes, struct cliente arrayClientes[]){
  
    char buffer[250];
    int j;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j].descriptor == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j].descriptor = arrayClientes[j+1].descriptor);
    
    (*numClientes)--;
    
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);

}

void salirPartida(int descriptor, int numPartida, struct partida arrayPartidas[]){

	//Tenemos que redimensionar el vector de clientes de la partida y quitar 1 al numClientes
	int i;
	for(i=0; i<arrayPartidas[numPartida].numClientes; i++)
		if(arrayPartidas[numPartida].clientes[i].descriptor == descriptor)
			break;
	for(; i<arrayPartidas[numPartida].numClientes; i++){
		(arrayPartidas[numPartida].clientes[i] = arrayPartidas[numPartida].clientes[i+1]);
	}

	arrayPartidas[numPartida].numClientes -=1;

	if(arrayPartidas[numPartida].numClientes==0){
		//Se han ido todos asi que limpiamos la partida
		limpiaPartida(arrayPartidas, numPartida);
		printf("Partida %d terminada por abandono de clientes\n", numPartida);
		fflush(stdout);
	}
}

void cartonABuffer(char * buffer, int ** carton){
	int i,j;
	char aux[20];
	bzero(buffer, sizeof(buffer));
	sprintf(buffer, "CARTON|");

	//Ahora tenemos que recorrer la matriz añadiendo los numeros al buffer

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(carton[i][j]!=0){
				sprintf(aux, "%d", carton[i][j]);
			}else{
				sprintf(aux, "X");
			}

			if(j<8){
				strcat(aux, ",");
			}

			strcat(buffer, aux);
			bzero(aux, sizeof(aux));
		}
		if(i<2){
			strcat(buffer, ";");
		}
	}

	strcat(buffer, "|");
	strcat(buffer, "\n");
}

void muestraBufferCartonBonito(char * buffer){
	//Reservamos memoria para el carton
	int i=0,j=0;
	char bufferDef[500];

	strncpy(bufferDef, buffer+5, 500);
  	char * pch;
  	pch = strtok (bufferDef,"|,;");
  	while (pch != NULL){
   		
   		pch = strtok (NULL, "|,;");
   		if(strcmp(pch, "X")==0){
   			printf("\033[31m%s\t", pch);
   		}else{
   			printf("\033[32m%s\t",pch);
   		}
   		j++;
   		if(j==9){
   			printf("\n");
   			i++;
   			j=0;
   		}
   		if(i==3 && j==0){
   			//Aqui ya ha terminado de rellenar la matriz
   			break;
   		}

  	}
  	printf("\e[0m");
	
}

void limpiaPartida(struct partida arrayPartidas[], int numPartida){

	int i;
	arrayPartidas[numPartida].estado = 0;
	arrayPartidas[numPartida].numClientes=0;
	arrayPartidas[numPartida].numBolas=0;
	for(i=0; i<90; i++){
		arrayPartidas[numPartida].bolas[i]=0;
	}
}