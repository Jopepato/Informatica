#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status, died;

    char *args[] = {"/bin/ls", "-t", "-l", (char *) 0 };

    switch(pid=fork())
    {
    case -1:
        printf("can't fork\n");
        exit(-1);
    case 0 :
        printf("child\n"); // código que ejecuta el hijo
        execv("/bin/ls", args);
    default:
        died= wait(&status); // código que ejecuta el padre
    }

    printf("died=%d (%d)\n",died,WEXITSTATUS(status));

    return(0);
}
