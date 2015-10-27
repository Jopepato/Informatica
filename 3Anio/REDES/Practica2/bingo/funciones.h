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

//Tenemos que hacer las estructuras de las partidas y clientes

struct cliente{

};

struct partida{

};



#endif
