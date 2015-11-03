#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
//Includes de las librerias para que funcione el cliente servidor

int main(int argc, char ** argv){
	
	if(argc!=3){
		printf("Hay que introducir la IP y el timeout\n");
	}

  struct sockaddr_in servidor;
  int descriptor;
  int envio, recibido=0;
  char mensajeRec[100];
  char mensaje[100];
  struct timeval timeout;
  int salida; //Salida del select
  int contador=0;
  fd_set lectura; //Para el select



  //Le asignamos los datos al sockaddr
  servidor.sin_family = AF_INET;
  servidor.sin_addr.s_addr = inet_addr(argv[1]);
  servidor.sin_port = htons(2000);
  int longitud_Servidor = sizeof(servidor);

  //Cogemos el descriptor
  descriptor = socket(AF_INET, SOCK_DGRAM, 0);
  if (descriptor == -1)
  {
    printf ("No se puede abrir socket servidor\n");
    return (-1);
  }
  printf("Introduce la opcion: ");
  scanf("%s", mensaje);


  //Vamos a enviarle un mensaje al servidor



  
  while(contador<3 && recibido==0){
  
    envio = sendto (descriptor, &mensaje, sizeof(mensaje), 0, (struct sockaddr *) &servidor, longitud_Servidor);
    if(envio < 1){
      printf("Error al solicitar el servicio de envio\n");
    }

      FD_ZERO(&lectura);
      FD_SET(descriptor, &lectura);

      //Fijamos el timeout para el select
      timeout.tv_sec = atoi(argv[2]);
      timeout.tv_usec=0;

    salida = select(descriptor+1, &lectura, NULL, NULL, &timeout); //Ponemos el select despues del envio, esperando la respuesta

    if(salida ==-1){
      printf("Se ha producido un error en el select\n");
      return -1;
    }else if(salida==0){
      printf("Se ha agotado el tiempo\n");
      contador++;
    }else {
        //Ahora esperamos la respuesta del server
        recibido = recvfrom(descriptor, (char*)&mensajeRec, sizeof(mensajeRec), 0, (struct sockaddr*) &servidor, &longitud_Servidor);

        if(recibido>0){
          printf("%s\n", mensajeRec);
        }else{
          printf("Ningun mensaje de vuelta\n");
        }
      }

   }

   if(contador==3){
    printf("Se han realizado 3 intentos\n");
   }
  close(descriptor);
  return 0;
}
