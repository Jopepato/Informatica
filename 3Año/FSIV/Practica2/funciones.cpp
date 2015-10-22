#include "funciones.hpp"



void help(){

	cout << "Ayuda con los comandos: " << endl;
	cout << "-h: Muestra la ayuda del programa" << endl;
	cout << "-i nombreImagen: Imagen que se va a cargar para el programa" << endl;
	cout << "-m nombreMascara: Nombre de la mascara a usar" << endl;
	cout << "-r radio: Radio que vamos a usar" << endl;
	cout << "-o nombreImagen Salida: Nombre del fichero donde se guardará la imagen de salida" << endl;

}

void calcHistograma(const Mat &imagen, vector<double> &histograma){
	//Calculamos el histograma con el vector, que seran las veces que aparece cada color
	double aux;
	//Ponemos el histograma a 0
	for(int i=0; i<256; i++)
		histograma[i]=0;

		//Recorremos la imagen
		for(int i=0; i<imagen.rows; i++){
			for(int j=0; j<imagen.cols; j++){
				aux = imagen.at<uchar>(i,j);
				histograma[aux]++;
			}
		}
	


}


void calcHistogramaMascara(const Mat &imagen,const Mat &mascara, vector<double> &histograma){

	double aux;
	for(int i=0; i<256; i++)
		histograma[i]=0;
	
		//Recorremos la imagen
		for(int i=0; i<imagen.rows; i++){
			for(int j=0; j<imagen.cols; j++){
				//Miramos la mascara
				if(mascara.at<uchar>(i,j)!=0){
					aux = imagen.at<uchar>(i,j);
					//Con esto tendriamos el histograma
					histograma[aux]++;
				}
			}
		}

}

void ecualizar(Mat &imagen, vector<double> &v){
	double aux;

		//Recorremos la imagen entera

		for(int i=0; i<imagen.rows; i++){
			for(int j=0; j<imagen.cols; j++){
				aux = imagen.at<uchar>(i,j);
				imagen.at<uchar>(i,j) = v[aux];
			}
		}



}


void ecualizarMascara(Mat &imagen,const Mat &mascara, vector<double> &v){

	double aux;

	//Recorremos la imagen

	for(int i=0; i<imagen.rows; i++){
		for(int j=0; j<imagen.cols; j++){
			if(mascara.at<uchar>(i,j)!=0){
				aux = imagen.at<uchar>(i,j);
				imagen.at<uchar>(i,j) = v[aux];
			}
		}
	}
}

void ecualizarRadio(Mat &imagen, vector<double> &v, int x, int y){

	double valor;
	valor = imagen.at<uchar>(x,y);
	imagen.at<uchar>(x,y) = v[valor];

}

void ecualizarMascaraRadio(Mat &imagen, const Mat &mascara, vector<double> &v, int x, int y){

	double valor;
	if(mascara.at<uchar>(x,y)!=0){
		valor = imagen.at<uchar>(x,y);
		imagen.at<uchar>(x,y) = v[valor];
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