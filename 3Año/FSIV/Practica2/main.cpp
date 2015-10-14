#include "funciones.hpp"

int main(int argc, char ** argv){

//Si nos dan una imagen en RGB la tenemos que pasar a HSV
cv::Mat imagenRGB, imagenHSV;
string nombreImg;

cout << "Introduce el nombre de la imagen: ";
cin >> nombreImg;

imagenRGB = imread(nombreImg, -1);
	if(!imagenRGB.empty()){
		cout << "Imagen cargada con exito"<< endl;
	}else{
		cout << "Problema al cargar la imagen" << endl;
		exit(-1);
	}

//La mostramos en RGB
namedWindow("ImagenRGB",CV_WINDOW_AUTOSIZE);
imshow("ImagenRGB", imagenRGB);
waitKey(0);


//La pasamos a HSV y la mostramos
cout << "La pasamos a HSV" << endl;

cvtColor(imagenRGB, imagenHSV, CV_BGR2HSV);

namedWindow("ImagenHSV", CV_WINDOW_AUTOSIZE);
imshow("ImagenHSV", imagenHSV);
waitKey(0);



}
