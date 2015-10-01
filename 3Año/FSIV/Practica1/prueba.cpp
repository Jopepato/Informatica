#include "funciones.hpp"

//g++ -Wall prueba.cpp -o prueba `pkg-config opencv --cflags --libs`

int main(){

	//Con este programa vamos a cargar una imagen
	cv::Mat imagen;
	cv::Mat mascara;
	cv::Mat imagenFinal;
	std::vector<cv::Mat> canal;
	std::string nombreImagen;
	std::cout << "Introduce el nombre de la imagen que quieres cargar: ";
	std::cin >> nombreImagen;

	imagen = cv::imread(nombreImagen, -1);//Con esto cargamos la imagen de la forma en la que esta sin aplicarle filtro alguno
		if(imagen.empty()){
			std::cout << "No se ha podido cargar la imagen" << std::endl;
			exit(-1);
		}else{
			std::cout << "Imagen cargada con exito" << std::endl;
			//cv::namedWindow("Ventana a", CV_WINDOW_AUTOSIZE);//Creamos una ventana para reescalar la imagen por si tiene mayor resolucion que nuestra pantalla
			//cv::imshow("Ventana", imagen);//Mostramos la imagen en dicha ventana que acabamos de crear
			//cv::waitKey(0);//Esto se debe de poner despues del imshow puesto que si no se pone el programa se cerrara y no mostrara nada
					//Con esto esperamos hasta que el usuario pulse alguna tecla asi se abrira la ventana de la imagen de forma indefinida
		}

		std::cout << "La imagen tiene: " << imagen.rows << " filas y " << imagen.cols << " columnas." << std::endl;
		int canales = imagen.channels();
		std::cout << "Y tiene " << canales << " canales" << std::endl;
/*
		std::cout << "Introduce el nombre de la mascara: ";
		std::cin >> nombreImagen;
		mascara = cv::imread(nombreImagen, -1);
		if(mascara.empty()){
			std::cout << "No se ha podido cargar la mascara" << std::endl;
			exit(-1);
		}
*/
		//Aplicamos la mascara a la imagen
		//imagen.copyTo(imagenFinal, mascara);
		

		cv::split(imagen, canal);	
		//Mostramos los estadisticos de la imagen
		for(int i=0; i<canales; i++){
			std::cout << "Canal: " << i << std::endl;
			estadisticos(canal[i], canal[i].rows, canal[i].cols);
			std::cout << std::endl << std::endl;
		}


	return (1);
}


