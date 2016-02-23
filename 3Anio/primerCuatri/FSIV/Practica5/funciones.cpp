#include "funciones.hpp"


void help(){
	cout << "Ayuda con los comandos: " << endl;
	cout << "-h: Muestra la ayuda del programa" << endl;
	cout << "-i nombreImagen: Imagen binaria de entrada" << endl;
	cout << "-o nombreFicheroSalida: Nombre del fichero de salida" << endl;
	cout << "-n valor: Valor para los 'n' descriptores de Fourier" << endl;
}


//Tenemos que cambiar esto para que solo guarde el vector de puntos que queremos
void contornoAFichero(const vector<Point> &contorno, const string &nombreFichero){
	//Guardamos el vector de contornos a fichero

	//Abrimos el fichero
	ofstream fichero;

	fichero.open(nombreFichero.c_str());

	if(!fichero.is_open()){
		cout << "No se ha podido abrir el fichero" << endl;
		exit(-1);
	}
		
	for(int i=0; i<contorno.size(); i++){
		//Vamos guardando a fichero
		fichero << contorno[i].x << " " << contorno[i].y << endl;
	}
	
	fichero.close();
}

void seleccionaMayorContorno(const vector<vector<Point > >&contours, vector<Point> &contorno){
	//Devuelve el contorno mas grande que va a ser el contorno de la figura
	int max=0;
	int k=0;

	for(int i=0; i<contours.size(); i++){
		//Recorremos todos los contornos y nos quedamos con el mayor
		if(contourArea(contours[i], false) > max){
			max = contourArea(contours[i], false);
			k=i;
		}

	}

	contorno = contours[k];
}

void calculaParametros(struct parametros &params, const vector<Point> &contorno){
	//Aqui calcularemos los parametros del contorno
	vector<Point> hull;
	params.longitud = arcLength(contorno, true);
	params.area = contourArea(contorno, false);
	convexHull(contorno, hull);
	params.solidez = (double)(params.area)/(double)(contourArea(hull,false));

	//Nos da el rectangulo básico
	params.rectanguloBasico = minAreaRect(contorno);

	params.boundingBox = boundingRect(contorno);

	//Ahora calculamos la excentricidad
	if(params.boundingBox.width > params.boundingBox.height){
		params.excentricidad = (double)params.boundingBox.width/(double)params.boundingBox.height;
	}else{
		params.excentricidad = (double)params.boundingBox.height/(double)params.boundingBox.width;
	}

	calculaDiametro(params, contorno);

	params.ocupacion = params.area/((double)params.boundingBox.width * (double)params.boundingBox.height);
	params.ocupaConvex = (double)(contourArea(hull,false))/((double)params.boundingBox.width * (double)params.boundingBox.height);

	params.compacidad = params.area/(double)pow(params.longitud, 2);
}


void muestraParametros(struct parametros params){
	//Funcion para mostrar los parametros por pantalla

	cout << "Longitud: \t" << params.longitud << endl;
	cout << "Diametro: \t" << params.diametro << endl;
	cout << "Area: \t\t" << params.area << endl;

	cout << "Rect. basico: \t" << "angulo: " << params.rectanguloBasico.angle
	 << " centro: " << params.rectanguloBasico.center.x << ", "
	 << params.rectanguloBasico.center.y << " lados: " << params.rectanguloBasico.size.height << ", "
	  << params.rectanguloBasico.size.width << endl;
	  //Fin del rectangulo

	cout << "Excentricidad: \t" << params.excentricidad << endl;
	cout << "Bounding box: \t[" << params.boundingBox.width << " x " << params.boundingBox.height
	<< "] from (" <<params.boundingBox.x << ", " << params.boundingBox.y << ")"  << endl;
	cout << "Ocupacion: \t" << params.ocupacion << endl;
	cout << "Compacidad: \t" << params.compacidad << endl;
	cout << "Ocup. Convexa: \t" << params.ocupaConvex << endl;
	cout << "Solidez: \t" << params.solidez << endl;
	cout << "Descriptores de fourier [ ";
		for(int i=0; i<params.n; i++){
			cout << params.fourier[i] << " , ";
		}
	cout << "]" << endl;
}

void calculaDiametro(struct parametros &params, const vector<Point> &contorno){

	double distancia = 0;
	double maxDistancia=0;

	for(int i=0; i<contorno.size(); i++){
		for(int j=i+1; j<contorno.size(); j++){
			//Ahora vamos calculando las distancias entre puntos
			distancia = sqrt(pow(contorno[i].x - contorno[j].x, 2) + pow(contorno[i].y - contorno[j].y,2));
			if(distancia> maxDistancia){
				maxDistancia = distancia;
			}
		}
	}

	//La maxima distancia será el parametro
	params.diametro = maxDistancia;

	calculaFourier(params, contorno);
}

void calculaFourier(struct parametros &params, const vector<Point> &contorno){

	int optimalSize = getOptimalDFTSize(contorno.size());
	vector<Point2f> vecAux;
	double maximo=0;
	vector<double> fourier;

	for(int i=0; i<optimalSize; i++){
		vecAux.push_back(contorno[i%contorno.size()]);
	}

	dft(vecAux, vecAux);

	for(int i=0; i<vecAux.size(); i++){
		fourier.push_back(sqrt(pow(vecAux[i].x,2) + pow(vecAux[i].y,2)));
		if(fourier[i]>maximo){
			maximo = fourier[i];
		}
	}

	//Lo normalizamos
	for(int i=0; i<fourier.size(); i++){
		fourier[i] = fourier[i]/maximo;
	}

	//Y metemos los n primeros
	for(int i=0; i<params.n; i++){
		params.fourier.push_back(fourier[i+1]);
	}

	
}
