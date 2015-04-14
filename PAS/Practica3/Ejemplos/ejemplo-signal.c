/* Cabeceras */
#include <stdio.h>      /* Entrada salida */
#include <stdlib.h>     /* Utilidades generales */
#include <signal.h>     /* Manejo de señales */
#include <unistd.h>

/*
Utilizando la utilidad kill, prueba a mandar señales a este programa. Ejecuta el programa en el background:

    ./ejemplo-signal &

Luego manda una señal, por ejemplo:

    kill -SIGHUP pid

(el pid del último proceso ejecutado en backgroud se puede obtener en bash con $!)

Prueba a mandar la señal por defecto. ¿Cuál es?:

    kill pid
*/


/* Este será nuestro manejador (personalizado) de señales SIGINT.
   SIGINT se genera cuando el usuario pulsa Ctrl-C.
   El comportamiento por defecto de un programa al pulsar Ctrl-C es salir.
   Con nuestro nuevo manejador, no saldrá. */
void mi_manejador_sigint(int signal)
{
    printf("Capturé la señal SIGINT y no salgo!\n");
    return;
}

/* Nuestro manejador para SIGKILL */
void mi_manejador_sigkill(int signal)
{
    printf("Capturé la señal SIGKILL y no salgo!\n");
    return;
}

/* Nuestro manejador para SIGHUP */
void mi_manejador_sighup(int signal)
{
    printf("Capturé la señal SIGHUP y no salgo!\n");
    return;
}

/* Nuestro manejador para SIGTERM */
void mi_manejador_sigterm(int signal)
{
    int i;
    printf("Capturé la señal SIGTERM y voy a salir de manera ordenada\n");
    for(i=0; i<3; i++){
        printf("Hasta luego... cerrando ficheros...\n");
        sleep(2);
    }
    exit(0);
}

int main()
{
    /* Utilizar la función signal() para asociar nuestras funciones a las señales
       SIGINT, SIGHUP y SIGTERM */
    if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGHUP, mi_manejador_sighup) == SIG_ERR)
        printf("No puedo asociar la señal SIGHUP al manejador!\n");
    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

    /* ¿Podemos asociar SIGKILL? */
    if (signal(SIGKILL, mi_manejador_sigkill) == SIG_ERR)
        printf("No puedo asociar la señal SIGKILL al manejador!\n");

    while(1){
	sleep(9);
    }  /* Bucle */

    /* exit */
    exit(0);  //¿Llegaremos aquí?
} /* main() */
