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
#define MSG_SIZE 512

struct cliente{
	int descriptor;
	char usuario[50];
	char password[50];
	int carton[3][9];
	int estado; //0 acaba de llegar
				//1 login
				//2 registro
};

struct partida{
	struct cliente clientes[4];
	int bolas[100];
	int numClientes;
};

int compruebaElementoVector(int * vector, int elem,int nelem);
int compruebaElementoMatriz(int ** matriz, int elem);
int ** generaCarton();
void muestraCarton(int ** carton);
int registroUsuario(char usuario[50], char password[50]);// 1 si registrado, 0 si nombre ya repetido
int compruebaUsuario(char usuario[50]);// 1 si verdad, 0 si falso
int compruebaUsuarioPassword(char usuario[50], char password[50]);//1 si verdad, 0 si falso


#endif