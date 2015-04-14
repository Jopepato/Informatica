#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status, died;

    switch(pid=fork())
    {
    case -1:
        printf("can't fork\n");
        exit(-1);
    case 0 :
        sleep(2); // código que ejecuta el hijo
        exit(3);
    default:
        died= wait(&status); // código que ejecuta el padre
    }
    printf("died=%d (%d)\n",died,WEXITSTATUS(status));

    return(0);
}
