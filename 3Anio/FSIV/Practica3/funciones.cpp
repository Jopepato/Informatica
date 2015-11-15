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

void butterworth(Mat &filtro, float r, int n){

	Mat aux = Mat(filtro.rows, filtro.cols, CV_32F);

	Point centro = Point(filtro.rows/2, filtro.cols/2);
	double radio;

	for(int i=0; i<filtro.rows; i++){
		for(int j=0; j<filtro.cols; j++){
			radio = (double)sqrt(pow(i-centro.x, 2.0) + pow((double)(j-centro.y), 2.0));
			aux.at<float>(i,j) = (float)(1/(1+pow((double)(radio/r),(double) (2*n))));
		}
	}

	Mat toMerge[] = {aux, aux};

	merge(toMerge, 2, filtro);
}

void shiftDFT(Mat &fImage){
 	
 	Mat tmp, q0, q1, q2, q3;

	int cx = fImage.cols/2;
	int cy = fImage.rows/2;

		q0 = fImage(Rect(0, 0, cx, cy));
		q1 = fImage(Rect(cx, 0, cx, cy));
		q2 = fImage(Rect(0, cy, cx, cy));
		q3 = fImage(Rect(cx, cy, cx, cy));

		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);

		q1.copyTo(tmp);
		q2.copyTo(q1);
		tmp.copyTo(q2);
}

Mat create_spectrum(Mat &complexImg){
	Mat planes[2];

	split(complexImg, planes);
	magnitude(planes[0], planes[1], planes[0]);

	Mat magI = planes[0];
	magI +=Scalar::all(1);
	log(magI, magI);

	shiftDFT(magI);

	normalize(magI, magI, 0, 1, CV_MINMAX);

	return magI;

}