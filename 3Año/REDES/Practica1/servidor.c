#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
//Includes de las librerias para que funcione el cliente servidor

int main(){

  struct sockaddr_in servidor;
  struct sockaddr_in cliente;
  char * buffer;
  char * mensaje;
  int recibido;

  int longitud_cliente = sizeof(cliente);
  int descriptor;



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

      //Aqui le enviaremos un mensaje al cliente si el servidor ha recibido algo
      sendto (descriptor, &mensaje, sizeof(mensaje), 0, (struct sockaddr *) &cliente, longitud_cliente);
      printf("Mensaje recibido\n");
    }

  }


  //Al final de todo deberemos cerrar el socket
  close(descriptor);
}
