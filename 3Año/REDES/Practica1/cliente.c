#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
//Includes de las librerias para que funcione el cliente servidor

int main(){

  struct sockaddr_in servidor;
  int descriptor;
  int envio, recibido;
  char mensajeRec[100];
  char mensaje[100];

  //Le asignamos los datos al sockaddr
  servidor.sin_family = AF_INET;
  servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
  servidor.sin_port = htons(2000);
  int longitud_Servidor = sizeof(servidor);

  descriptor = socket(AF_INET, SOCK_DGRAM, 0);
  if (descriptor == -1)
  {
    printf ("No se puede abrir socket servidor\n");
    return (-1);
  }
  printf("Introduce la opcion: ");
  scanf("%s", mensaje);


  //Vamos a enviarle un mensaje al servidor
  
    envio = sendto (descriptor, &mensaje, sizeof(mensaje), 0, (struct sockaddr *) &servidor, longitud_Servidor);
    if(envio < 1){
      printf("Error al solicitar el servicio de envio\n");
    }

    //Ahora esperamos la respuesta del server
    recibido = recvfrom(descriptor, (char*)&mensajeRec, sizeof(mensajeRec), 0, (struct sockaddr*) &servidor, &longitud_Servidor);

    if(recibido>0){
      printf("%s\n", mensajeRec);
    }else{
      printf("Ningun mensaje de vuelta\n");
    }


  close(descriptor);
}
