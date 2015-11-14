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

using namespace cv;
using namespace std;

int main(int argc, char ** argv){

string nombreVideo = argv[1];
int t = atoi(argv[2]);
VideoCapture cap(nombreVideo);
VideoCapture cap2(nombreVideo);
pMOG2;
int contador=0;
int key;
string salida;
string sal = "sal_";
string png = ".png";
ostringstream convert;
int empieza=0;
Mat frame, edges;
Mat frame2, edges2;
Mat foreground;

if(!cap.isOpened()){
	cout << "Video especificado invalido" << endl;
	exit(-1);
}

    //namedWindow("edges",1);
    while(true){
        
        
        cap >> frame; // get a new frame from camera

        cvtColor(frame, edges, CV_BGR2GRAY);
        pMOG2->apply(frame, frame2);
/*
        if(empieza=1){
            //Empieza un fotograma despues
            
            cap2 >> frame2;
            //Esto va un fotograma atrasado
            cvtColor(frame2, edges2, CV_BGR2GRAY);

            //Ahora comparamos ambas imagenes y vemos que es lo que queremos mostrar
            //Para mostrar solamente el foreground
            /*for(int i=0; i<edges.rows; i++){
                for(int j=0; j<edges.cols; j++){
                    //Comparamos ambos pixeles
                    if(abs(edges.at<float>(i,j)-edges2.at<float>(i,j))<t){
                        edges2.at<float>(i,j) = 0;
                    }
                }
            }
            
        }
*/
        imshow("frames", frame);
        imshow("gris", edges);
        imshow("foreground", frame2);
        key = waitKey(25);
        empieza=1;

        if(key==27){
            //Ha pulsado escape asi que nos salimos
            break;
        }

    }

cap.release();

return 0;

}






/****************************************
            COSAS QUE INCLUIR
****************************************/




//Para coger el numero de frame que estamos viendo
//Lo metemos en un stringstream
//stringstream ss
// ss << capture.get(CAP_PROP_POS_FRAMES)

//Esto es para lo de guardar una imagen y parar el video y eso

        /*salida.clear();
        convert << contador;
        salida = sal + convert.str() + png;
        key = waitKey(25);
        //Ahora miramos la tecla que ha pulsado
        if(key==32){
            //Guardamos la imagen
            imwrite(salida.c_str(), frame);
        }

        if(key==27){
            //Ha pulsado escape asi que nos salimos
            break;
        }
        contador++;
        */