#include "funciones.hpp"


void estadisticosMask(const cv::Mat &matriz,const cv::Mat &mascara, const int fil, const int col){

	double media=0;
	double aux = matriz.at<uchar>(0,0);//Donde almacenaremos el pixel de la matriz para recorrerlo
	double suma;
	double sumaCuadrados;
	double varianza;
	double asimetria=0;
	double contador;
	int numCeros=0;
	int numPos=0;
	double sumaPos=0;
	int numNeg=0;
	double sumaNeg=0;
	int menor=aux;
	int mayor=aux;
		for(int i=0; i<fil;i++){
			for(int j=0; j<col; j++){
				if(mascara.at<uchar>(i,j)==255.0){
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
						if(aux >0.0){
							numPos++;
							sumaPos = sumaPos + aux;
						}
						if(aux <0.0){
							numNeg++;
							sumaNeg = sumaNeg + aux;
						}
						contador++;
					}
			}

		}

	suma = media;
	media = media/contador;
	varianza = (sumaCuadrados/contador)-pow(media,2);
	//distopia = sqrt(varianza);


	

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
	std::cout << "El coeficiente de asimetria es: " << asimetria << std::endl;


}


void estadisticos(const cv::Mat &matriz, const int fil, const int col){


	double media=0;
	double aux = matriz.at<uchar>(0,0);//Donde almacenaremos el pixel de la matriz para recorrerlo
	double suma;
	double sumaCuadrados=0;
	double sumaCubos=0;
	double varianza;
	double asimetria=0.0;
	double desviacion;
	double sumaMediaCubo=0;
	int contador=0;
	int numCeros=0;
	int numPos=0;
	double sumaPos=0;
	int numNeg=0;
	double sumaNeg=0;
	int menor=aux;
	int mayor=aux;
		for(int i=0; i<fil;i++){
			for(int j=0; j<col; j++){
					aux = matriz.at<uchar>(i,j);
					media = media + aux;
					sumaCuadrados = sumaCuadrados + pow(aux, 2);
					sumaCubos = sumaCubos + pow(aux, 3);
						if(aux<menor){
							menor = aux;
						}
						if(aux>mayor){
							mayor = aux;
						}
						if(aux == 0){
							numCeros++;
						}
						if(aux >0.0){
							numPos++;
							sumaPos = sumaPos + aux;
						}
						if(aux <0.0){
							numNeg++;
							sumaNeg = sumaNeg + aux;
						}
						contador++;
			}

		}

	suma = media;
	media = media/contador;
	varianza = (sumaCuadrados/contador)-pow(media,2);
	
	desviacion = sqrt(varianza);
		
	//Voy a hacer algo nuevo
	double cosa=0.0;
	for(int i=0; i<fil; i++){
		for(int j=0; j<col;j++){
			aux = matriz.at<uchar>(i,j);
			//sumaMediaCuadrado += pow(aux-media,2);
			cosa = aux -media;
			sumaMediaCubo = sumaMediaCubo + pow(cosa,3);	

		}
	}

	asimetria = sumaMediaCubo/(pow(desviacion,3)*(contador));
	

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
	std::cout << "El coeficiente de asimetria es: " << asimetria << std::endl;


}