/* Includes */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <signal.h>     /* Signal handling */
#include <unistd.h>

/*
Try sending signals to this program through the command-line using the kill utility. First run the program in the background:

    ./signals-ex &

Then try sending a signal, for example:

    kill -SIGHUP pid

Try killing the process:

    kill pid
*/
/* This will be our new SIGINT handler.
   SIGINT is generated when user presses Ctrl-C.
   Normally, program will exit with Ctrl-C.
   With our new handler, it won't exit. */

// v es un indicador del recurso que queremos liberar
int v=0;


void mysigint()
{
    printf("I caught the SIGINT signal!\n");
    return;
}

/* Our own SIGKILL handler */
void mysigkill()
{
    printf("I caught the SIGKILL signal!\n");
    return;
}

/* Our own SIGHUP handler */
void mysighup()
{
    printf("I caught the SIGHUP signal!\n");
    return;
}

/* Our own SIGTERM handler */
void mysigterm()
{
    printf("I caught the SIGTERM signal!\n");
    printf("mi PID es %d, y mi v %d\n", getpid(), v);
    printf("Hasta luego... cerrando ficheros...\n");
    sleep(2);
    exit(0);
    //return;
}



int main()
{
    /* Use the signal() call to associate our own functions with
       the SIGINT, SIGHUP, and SIGTERM signals */
    if (signal(SIGINT, mysigint) == SIG_ERR)
        printf("Cannot handle SIGINT!\n");
    if (signal(SIGHUP, mysighup) == SIG_ERR)
        printf("Cannot handle SIGHUP!\n");
    if (signal(SIGTERM, mysigterm) == SIG_ERR)
        printf("Cannot handle SIGTERM!\n");

    /* can SIGKILL be handled by our own function? */
    if (signal(SIGKILL, mysigkill) == SIG_ERR)
        printf("Cannot handle SIGKILL!\n");


    /* Crea 2 subprocesos */
    fork();
    fork();
    v = getpid()*2;   //Para simplificar, simplemente ponemos que v sea el pid por 2
    printf("mi PID es %d, y mi ppid%d\n", getpid(), getppid());

    while(1);  /* infinite loop */

    /* exit */
    exit(0);
} /* main() */
