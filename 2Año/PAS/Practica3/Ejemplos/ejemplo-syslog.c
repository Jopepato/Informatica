/*
 http://pubs.opengroup.org/onlinepubs/9699919799/
*/
#include <stdio.h>
#include <syslog.h>

int main()
{

    char *message = "Mensaje de prueba";
    int priority = LOG_ERR | LOG_USER; // LOG_INFO

    syslog(priority, message);

    printf("Ahora comprueba los últimos mensajes en syslog con \"tail /var/log/syslog\"\n");

    return 0;
}
