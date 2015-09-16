#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t rf;
    rf = fork();
    switch (rf)
    {
    case -1:
        printf ("No he podido crear el proceso hijo \n");
        exit(-1);
    case 0:
        printf ("Soy el hijo, mi PID es %d y mi PPID es %d \n", getpid(), getppid());
        sleep (12);
        break;
    default:
        printf ("Soy el padre, mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
        sleep (10); /* prueba a poner aquí un valor menor que 5 */
    }

    printf ("Final de ejecución de %d \n", getpid());
    exit (0);
}

