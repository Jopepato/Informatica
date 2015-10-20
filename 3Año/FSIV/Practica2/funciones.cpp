#include "funciones.hpp"



void help(){

	std::cout << "Ayuda con los comandos: " << std::endl;
	std::cout << "-h: Muestra la ayuda del programa" << std::endl;
	std::cout << "-i nombreImagen: Imagen que se va a cargar para el programa" << std::endl;
	std::cout << "-m nombreMascara: Nombre de la mascara a usar" << std::endl;
	std::cout << "-r radio: Radio que vamos a usar" << std::endl;

}

void calcHistograma(const Mat &imagen, vector<double> &histograma, int r){
	//Calculamos el histograma con el vector, que seran las veces que aparece cada color
	double aux;


		//Recorremos la imagen
		for(int i=r; i<imagen.rows-r; i++){
			for(int j=r; j<imagen.cols-r; j++){
				aux = imagen.at<uchar>(i,j);
				histograma[aux]++;
			}
		}
	


}


void calcHistogramaMascara(const Mat &imagen,const Mat &mascara, vector<double> &histograma, int r){

	double aux;

		//Recorremos la imagen
		for(int i=r; i<imagen.rows-r; i++){
			for(int j=r; j<imagen.cols-r; j++){
				//Miramos la mascara
				if(mascara.at<uchar>(i,j)!=0){
					aux = imagen.at<uchar>(i,j);
					//Con esto tendriamos el histograma
					histograma[aux]++;
				}
			}
		}

}

void ecualizar(Mat &imagen, vector<double> &v, int r){
	double aux;

		//Recorremos la imagen entera

		for(int i=r; i<imagen.rows-r; i++){
			for(int j=r; j<imagen.cols-r; j++){
				aux = imagen.at<uchar>(i,j);
				imagen.at<uchar>(i,j) = v[aux];
			}
		}



}


void ecualizarMascara(Mat &imagen,const Mat &mascara, vector<double> &v, int r){

	double aux;

	//Recorremos la imagen

	for(int i=r; i<imagen.rows-r; i++){
		for(int j=r; j<imagen.cols-r; j++){
			if(mascara.at<uchar>(i,j)!=0){
				aux = imagen.at<uchar>(i,j);
				imagen.at<uchar>(i,j) = v[aux];
			}
		}
	}




}

void rellenaVector(vector<double> &v){
	for(int i=0; i<256; i++){
		v.push_back(0);
	}
}

void vectorAcumulado(vector<double> &v){
	double acumulado=0;
	for(int i=0; i<=255; i++){
		acumulado = acumulado + v[i];
		v[i] = acumulado;
	}
}

void normalizaVector(vector<double> &v){
	double norma=v[255];
	for(int i=0; i<255; i++){
		v[i] = 255*v[i]/norma;
	}
}