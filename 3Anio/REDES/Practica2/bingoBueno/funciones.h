#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define MAX_CLIENTES 40
#define MAX_PARTIDAS 10
#define MSG_SIZE 512

struct cliente{
	int descriptor;
	char usuario[50];
	char password[50];
	int ** carton;
	int estado; //0 acaba de llegar
				//1 login con usuario correcto
				//2 usuario y pass correcta, tenia que tener un 1
				//3 buscando partida, tendria que tener un 2 De esta se puede salir
				//4 en partida
};

struct partida{
	struct cliente clientes[5];
	int bolas[90];
	int numClientes;
	int numBolas;
	int estado; // 0 Aun no ha empezado
				// 1 Ha empezado
				// 2 Han cantado linea
				// 3 Han cantado 2lineas
				// 4 han cantado bingo, por lo que se dejaria vacia la partida
};

int compruebaElementoVector(int * vector, int elem, int nelem);
int compruebaElementoMatriz(int ** matriz, int elem);
int ** generaCarton();
void muestraCarton(int ** carton);
int registroUsuario(char usuario[50], char password[50]);// 1 si registrado, 0 si nombre ya repetido
int compruebaUsuario(char usuario[50]);// 1 si verdad, 0 si falso
int compruebaUsuarioPassword(char usuario[50], char password[50]);//1 si verdad, 0 si falso
int devuelvePosicion(struct cliente arrayClientes[MAX_CLIENTES], int descriptor, int numClientes);//Devuelve la posicion del cliente en el array segun su descriptor
void estadoPartidasA0(struct partida arrayPartidas[10]);//Inicializa todos los campos de la partida a 0
int getBola(int arrayBolas[]);//Devuelve una bola no repetida en el vector
int getPartida(struct partida arrayPartidas[], int descriptor); //Devuelve el numero de partida en el array de partida, segun el descriptor del cliente
int compruebaLinea(int ** carton, int bolas[], int numBolas);//Devuelve 0 si falso, 1 si verdad
int compruebaDosLineas(int ** carton, int bolas[], int numBolas);//Devuelve 0 si falso, 1 si verdad
int compruebaBingo(int ** carton, int bolas[], int numBolas);//Devuelve 0 si falso, 1 si verdad
void salirServidor(struct cliente arrayClientes[], int sd, int numClientes, fd_set * readfds);
void salirCliente(int socket, fd_set * readfds, int * numClientes, struct cliente arrayClientes[]);
void salirPartida(int descriptor, int numPartida, struct partida arrayPartidas[]);
void cartonABuffer(char * buffer, int ** carton);
void muestraBufferCartonBonito(char * buffer);
void limpiaPartida(struct partida arrayPartidas[], int numPartida);
void limpiaCartonCliente(struct cliente arrayClientes[], int numCliente);
void manejador(int signum);

#endif