#include <ctype.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
#include "funciones.hpp"

using namespace cv;
using namespace std;

int main(int argc, char ** argv){

string nombreVideo;
string nombreVideoSalida = "salida.avi";
VideoCapture cap;
int t=5;
int iflag, tflag, oflag;
int contador=0;
int key;
char fotograma[21];
string salida;
string sal = "sal_";
string png = ".png";
int empieza=0;
Mat frame1, edges1;
Mat frame2, edges2;
Mat foreground;
Mat absDiff;
int opcion;

while((opcion=getopt(argc, argv, "i:t:o:h")) !=-1 ){

    switch(opcion){

      case 'h':
          help();
          exit(EXIT_SUCCESS);
        break;

      case 'i':
        //Nombre del video dado por el usuario
        iflag=1;
        nombreVideo = optarg;
        break;

      case 't':
        tflag=1;
        t = atoi(optarg);

        break;

      case 'o':
        oflag = 1;
        //Para el nombre del video de salida
        nombreVideoSalida = optarg;
        break;

      case '?':
        //Algo ha ido mal
        help();
        exit(-1);
        break;

      default:
        help();
        exit(-1);
        break;
      }
  }

    if(iflag==1){
        cap.open(nombreVideo);
    }else{
        //Nombre del video necesario
        cout << "Nombre del video de entrada necesario" << endl;
        help();
        exit(-1);
    }


    if(!cap.isOpened()){
	cout << "Video especificado invalido" << endl;
	exit(-1);
    }

    //Creamos la ventana con la imagen principal y la barra
    namedWindow("Video", CV_WINDOW_AUTOSIZE);
    createTrackbar("Valor de t", "Video", &t, 250);

    cap >> frame1; //Primer frame
    

    while(true){
        
        //Esto va un fotograma atrasado
        cvtColor(frame1, edges1, CV_BGR2GRAY);
        

        cap.read(frame2); //Nuevo frame
            
        
        cvtColor(frame2, edges2, CV_BGR2GRAY);
        foreground = edges2.clone();

        absdiff(edges2, edges1, absDiff);
        //Ahora comparamos ambas imagenes y vemos que es lo que queremos mostrar
        //Para mostrar solamente el foreground
        for(int i=0; i<frame2.rows; i++){
            for(int j=0; j<frame2.cols; j++){

                if(absDiff.at<uchar>(i,j) > t){
                    foreground.at<uchar>(i,j) = 255;
                }else{
                    foreground.at<uchar>(i,j) = 0;
                }
            }
        }
        imshow("Video", frame2);
        imshow("gris", frame1);
        imshow("foreground", foreground);
        
        key = waitKey(30);
        empieza=1;
        if(key==27){
            //Ha pulsado escape asi que nos salimos
            break;
        }
        if(key==32){
            sprintf(fotograma, "%d", contador);
            salida = sal + fotograma + png;
            imwrite(salida.c_str(), frame1);
            bzero(fotograma, sizeof(fotograma));
            cout << "Imagen tomada" << endl;
        }
        //Nos lleva el numero de frames
        contador++;
        frame1 = frame2.clone(); //Con esto vamos un frame atrasados

    }

cap.release();

return 0;

}