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

int ** generaCarton();
int compruebaElementoVector(int vector[4], int elem);
int compruebaElementoMatriz(int ** matriz, int elem);
void muestraMatriz(int **carton);
void compruebaUsuario(char ** usuario);
void compruebaUsuarioPassword(char ** usuario, char ** password);
void guardaUsuarioPassword(char ** usuario, char ** password);

//Tenemos que hacer las estructuras de las partidas y clientes

struct cliente{
	char ** usuario;
	char ** password;
};

struct partida{

};



#endif
