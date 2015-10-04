#include "funciones.hpp"

void calculaEstadisticos(const cv::Mat &matriz){


	estadisticos est;

	double aux = matriz.at<uchar>(0,0);//Donde almacenaremos el pixel de la matriz para recorrerlo
	double desviacion;
	double sumaMediaCubo=0;
	est.menor=aux;
	est.mayor=aux;
	double contador=0.0;

		for(int i=0; i<matriz.rows;i++){
			for(int j=0; j<matriz.cols; j++){
						aux = matriz.at<uchar>(i,j);
						est.media += aux;
						est.sumaCuadrados += pow(aux, 2);
							if(aux<=est.menor){
								est.menor = aux;
							}
							if(aux>=est.mayor){
								est.mayor = aux;
							}
							if(aux == 0){
								est.numCeros+=1;
							}
							if(aux >0.0){
								est.numPos+=1;
								est.areaPos += aux;
							}
							if(aux <0.0){
								est.numNeg++;
								est.areaNeg += aux;
							}
							contador++;

			}

		}

	est.suma = est.media;
	est.media = est.media/contador;
	est.varianza = (est.sumaCuadrados/contador)-pow(est.media,2);
	
	desviacion = sqrt(est.varianza);

	double suma=0.0;
	for(int i=0; i<matriz.rows; i++){
		for(int j=0; j<matriz.cols;j++){
			suma = matriz.at<uchar>(i,j);
			suma = aux -est.media;
			sumaMediaCubo = sumaMediaCubo + pow(suma,3);	

		}
	}

	est.asimetria = sumaMediaCubo/(pow(desviacion,3)*(contador));

	muestraEstadisticos(est);
}


void calculaEstadisticosMascara(const cv::Mat &matriz, const cv::Mat &mascara){



	estadisticos est;

	double aux;
	double desviacion= 0.0;
	double sumaMediaCubo= 0.0;
	est.menor= 256.0;
	est.mayor= 0.0;
	double contador= 0.0;

		for(int i=0; i<matriz.rows;i++){
			for(int j=0; j<matriz.cols; j++){
					if(mascara.at<uchar>(i,j)==255.0){
						aux = matriz.at<uchar>(i,j);
						est.media += aux;
						est.sumaCuadrados += pow(aux, 2);
						contador++;
							if(aux<=est.menor){
								est.menor = aux;
							}
							if(aux>=est.mayor){
								est.mayor = aux;
							}
							if(aux == 0){
								est.numCeros+=1;
							}
							if(aux >0.0){
								est.numPos+=1;
								est.areaPos += aux;
							}
							if(aux <0.0){
								est.numNeg++;
								est.areaNeg += aux;
							}
							
						}
			}

		}

	est.suma = est.media;
	est.media = est.media/contador;
	est.varianza = (est.sumaCuadrados/contador)-pow(est.media,2);
	
	desviacion = sqrt(est.varianza);

	double suma=0.0;
	for(int i=0; i<matriz.rows; i++){
		for(int j=0; j<matriz.cols;j++){
			if(mascara.at<uchar>(i,j)==255.0){
				aux = matriz.at<uchar>(i,j);
				suma = aux -est.media;
				sumaMediaCubo = sumaMediaCubo + pow(suma,3);	
			}
		}
	}

	est.asimetria = sumaMediaCubo/(pow(desviacion,3)*(contador));

	muestraEstadisticos(est);

	
}



void muestraEstadisticos(const struct estadisticos &est){


	//Aqui vamos a mostrar todos los estadisticos de forma ordenada:
	std::cout << "El valor minimo es: " << est.menor << std::endl;
	std::cout << "El valor máximo es: " << est.mayor << std::endl;
	std::cout << "La media es: " << est.media << std::endl;
	std::cout << "La varianza es: " << est.varianza << std::endl;
	std::cout << "La suma es: " << est.suma << std::endl;
	std::cout << "La suma de cuadrados es: " << est.sumaCuadrados << std::endl;
	std::cout << "El area positiva es: " << est.areaPos << std::endl;
	std::cout << "El area negativa es: " << est.areaNeg << std::endl;
	std::cout << "El numero de ceros es: " << est.numCeros << std::endl;
	std::cout << "El numero de positivos es: " << est.numPos << std::endl;
	std::cout << "El coeficiente de asimetria es: " << est.asimetria << std::endl;

}

void help(){

	std::cout << "Ayuda con los comandos: " << std::endl;
	std::cout << "-h : Muestra la ayuda del programa" << std::endl;
	std::cout << "-v nombreImagen: Imagen que se va a cargar para el programa" << std::endl;
	std::cout << "-m nombreMascara: Nombre de la mascara a usar" << std::endl;
	std::cout << "-w x,y,w,h: Parametros para obtener la submatriz" << std::endl;
	std::cout << "-i: Modo interactivo para obtener la submatriz" << std::endl;

}

void calculaEstadisticosDef(cv::Mat &imagen, cv::Mat const &mascara, cv::Mat const &subImagen, cv::Mat const subMascara, int wflag, int iflag, int mflag){

	//En esta funcion lo que haremos sera comprobar que clase de cosa debemos hacer

	//Primero mostramos el numero de canales y canales de la imagen original

	std::vector<cv::Mat> canal;
	std::cout << "La imagen tiene " << imagen.rows << " filas y " << imagen.cols << " columnas" << std::endl;
	std::cout << "Canales " << imagen.channels() << std::endl; 


	//Ahora mirando los flags vemos que tenemos que hacer

	if(iflag==1||wflag==1){
		//Imagen con roi
		//Sacamos los canales de la submatriz
		cv::split(subImagen, canal);

		std::cout << "La region de interes tiene: " << std::endl;
		std::cout << "Filas: " << subImagen.rows << std::endl;
		std::cout << "Columnas: " << subImagen.cols << std::endl;

		for(int i=0; i<subImagen.channels(); i++){
			std::cout << "Canal: " << i << std::endl;
			if(mflag==1){
				//Con mascara
				calculaEstadisticosMascara(canal[i], subMascara);
			}else{
				//Sin mascara
				calculaEstadisticos(canal[i]);
			}
		}
	}else{

		//Spliteamos la imagen entera en canales
		cv::split(imagen, canal);

		for(int i=0; i<imagen.channels(); i++){
			std::cout << "Canal: " << i << std::endl;
			//Miramos si han introducido mascara
			if(mflag==1){
				//Con mascara
				calculaEstadisticosMascara(canal[i], mascara);
			}else{
				calculaEstadisticos(canal[i]);
			}
		}


	}

}

