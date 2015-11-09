#include "funciones.hpp"

void help(){

	cout << "Ayuda con los comandos: " << endl;
	cout << "-h: Muestra la ayuda del programa" << endl;
	cout << "-i nombreImagen: Imagen que se va a cargar para el programa" << endl;
	cout << "-m nombreMascara: Mascara a aplicar para la imagen" << endl;
	cout << "-o nombreImagenSalida: Imagen de salida segmentada" << endl;
	cout << "-r [0,1]: Frecuencia de corte del filtro" << endl;
	cout << "n [1,10]: Orden del filtro butterworth paso baja" << endl;
	cout << "g [0.0, 5.0]: Ganancia del realce" << endl;
}

void butterworth(Mat &filtro, float r, float n){
	Mat aux = Mat(filtro.rows, filtro.cols, CV_32F);

	Point centro = Point(filtro.rows/2, filtro.cols/2);
	double radio;

	for(int i=0; i<filtro.rows; i++){
		for(int j=0; j<filtro.cols; j++){
			radio = (double)sqrt(pow(i-centro.x, 2.0) + pow(j-centro.y, 2.0));
			aux.at<float>(i,j) = (float)(1/(1+pow(radio/r, 2*n)));
		}
	}

	Mat toMerge[] = {tmp, tmp};

	merge(toMerge, 2, filtro);
}