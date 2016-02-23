#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//Includes de las librerias para que funcione el cliente servidor

int main(){

  struct sockaddr_in servidor;
  struct sockaddr_in cliente;
  char buffer[100];
  char *mensaje;
  mensaje = (char*)malloc(100*sizeof(char));
  int recibido;
  time_t tiempo;
  struct tm *stTm;

  int longitud_cliente = sizeof(cliente);
  int descriptor;

tiempo = time(NULL);

  stTm = localtime(&tiempo);

  descriptor = socket(AF_INET, SOCK_DGRAM, 0);
  if (descriptor == -1)
  {
    printf ("No se puede abrir socket servidor\n");
    return(-1);
  }


  //Le asignamos los datos al sockaddr
  servidor.sin_family = AF_INET;
  servidor.sin_addr.s_addr = htonl(INADDR_ANY);
  servidor.sin_port = htons(2000);

  if(bind(descriptor, (struct sockaddr *)&servidor, sizeof(servidor))==-1){
    close(descriptor);
    printf("Something went wrong\n");
    return(-1);
  }


  //Hacemos el bucle para que el servidor este siempre escuchando Ü
  while(1){
    //Recibimos el mensaje del cliente
    recibido = recvfrom(descriptor, (char *)&buffer, sizeof(buffer), 0, (struct sockaddr *) &cliente, &longitud_cliente);


    if(recibido > 0){

	   if(strcmp(buffer, "DAY") == 0){

              strftime(buffer,100,"%A, %d of %B of %Y", stTm);

         }else if(strcmp(buffer, "DAYTIME") == 0){

               strftime(buffer,100,"%A, %d of %B of %Y; %H:%M:%S", stTm);

         }else if(strcmp(buffer, "TIME") == 0){

                strftime(buffer,100,"%H:%M:%S", stTm);

        }else{
          strcpy(buffer, "No coincide");
        }

      //Aqui le enviaremos un mensaje al cliente si el servidor ha recibido algo
      sendto (descriptor, &buffer, sizeof(buffer), 0, (struct sockaddr *) &cliente, longitud_cliente);
      printf("Mensaje recibido\n");
    }

  }


  //Al final de todo deberemos cerrar el socket
  close(descriptor);
}
