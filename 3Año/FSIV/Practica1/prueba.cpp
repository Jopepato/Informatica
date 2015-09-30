#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 

//g++ -Wall prueba.cpp -o prueba `pkg-config opencv --cflags --libs`

void estadisticos(const cv::Mat &matriz,const cv::Mat &mascara, const int fil, const int col);

int main(){

//Con este programa vamos a cargar una imagen
cv::Mat imagen;
cv::Mat mascara;
cv::Mat imagenFinal;
std::vector<cv::Mat> canal;
std::string nombreImagen;
int menu;
std::cout << "Introduce el nombre de la imagen que quieres cargar: ";
std::cin >> nombreImagen;

imagen = cv::imread(nombreImagen, -1);//Con esto cargamos la imagen de la forma en la que esta sin aplicarle filtro alguno
	if(imagen.empty()){
		std::cout << "No se ha podido cargar la imagen" << std::endl;
		exit(-1);
	}else{
		std::cout << "Imagen cargada con exito" << std::endl;
		cv::namedWindow("Ventana", CV_WINDOW_AUTOSIZE);//Creamos una ventana para reescalar la imagen por si tiene mayor resolucion que nuestra pantalla
		cv::imshow("Ventana", imagen);//Mostramos la imagen en dicha ventana que acabamos de crear
		cv::waitKey(0);//Esto se debe de poner despues del imshow puesto que si no se pone el programa se cerrara y no mostrara nada
				//Con esto esperamos hasta que el usuario pulse alguna tecla asi se abrira la ventana de la imagen de forma indefinida
	}

	std::cout << "La imagen tiene: " << imagen.rows << " filas y " << imagen.cols << " columnas." << std::endl;
	int canales = imagen.channels();
	std::cout << "Y tiene " << canales << " canales" << std::endl;

	std::cout << "Quieres utilizar una mascara en la imagen: 1.si 2.no ";
	std::cin >> menu;
	if(menu==1){
		std::cout << "Introduce el nombre de la mascara: ";
		std::cin >> nombreImagen;
		mascara = cv::imread(nombreImagen, -1);
		if(mascara.empty()){
			std::cout << "No se ha podido cargar la mascara" << std::endl;
			exit(-1);
		}
	}

	cv::split(imagen, canal);	
	//Mostramos los estadisticos de la imagen
	for(int i=0; i<canales; i++){
		std::cout << "Canal: " << i+1 << std::endl;
		estadisticos(canal[i],mascara, canal[i].rows, canal[i].cols);
		std::cout << std::endl << std::endl;
	}


return (1);
}


void estadisticos(const cv::Mat &matriz,const cv::Mat &mascara, const int fil, const int col){

double media=0;
double aux = matriz.at<uchar>(0,0);//Donde almacenaremos el pixel de la matriz para recorrerlo
double suma;
double sumaCuadrados;
double varianza;
int numCeros=0;
int numPos=0;
double sumaPos=0;
int numNeg=0;
double sumaNeg=0;
int menor=aux;
int mayor=aux;
	for(int i=0; i<fil;i++){
		for(int j=0; j<col; j++){
			if(mascara.at<uchar>(i,j)==0){
				aux = matriz.at<uchar>(i,j);
				media = media + aux;
				sumaCuadrados = sumaCuadrados + pow(aux, 2);
					if(aux<menor){
						menor = aux;
					}
					if(aux>mayor){
						mayor = aux;
					}
					if(aux == 0){
						numCeros++;
					}
					if(aux >0){
						numPos++;
						sumaPos = sumaPos + aux;
					}
					if(aux <0){
						numNeg++;
						sumaNeg = sumaNeg + aux;
					}
			}
		}

	}

suma = media;
media = media/(fil*col);
varianza = (sumaCuadrados/(fil*col))-pow(media,2);
std::cout << "La media es: " << media << std::endl;
std::cout << "El mayor es: " << mayor << std::endl;
std::cout << "El menor es: " << menor << std::endl;
std::cout << "La suma es: " << suma << std::endl;
std::cout << "La suma de cuadrados es: " << sumaCuadrados << std::endl;
std::cout << "La varianza es: " << varianza << std::endl;
std::cout << "El numero de elementos positivos es: " << numPos << std::endl;
std::cout << "El numero de elementos negativos es: " << numNeg << std::endl;
std::cout << "El numero de ceros es: " << numCeros << std::endl;
std::cout << "El area positiva es: " << sumaPos << std::endl;
std::cout << "El area negativa es: " << sumaNeg << std::endl;


}
