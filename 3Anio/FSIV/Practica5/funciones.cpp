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
		if(contours[i].size() > max){
			max = max;
			k=i;
		}

	}

	contorno = contours[k];
}

void calculaParametros(struct parametros &params, const vector<Point> &contorno){
	//Aqui calcularemos los parametros del contorno
	params.longitud = arcLength(contorno, true);
	params.area = contourArea(contorno, false);

	//Nos da el rectangulo básico
	params.rectanguloBasico = minAreaRect(contorno);

	params.ocupacion = boundingRect(contorno);

	params.rotatedRectangle.angulo = params.rectanguloBasico.angle;
	params.rotatedRectangle.centro = params.rectanguloBasico.center;
}


void muestraParametros(struct parametros params){
	//Funcion para mostrar los parametros por pantalla

	cout << "Longitud: \t" << params.longitud << endl;
	cout << "Diametro: \t" << "--" << endl;
	cout << "Area: \t" << params.area << endl;
	cout << "Rect. basico: \t" << "----" << endl;
	cout << "Excentricidad: \t" << "----" << endl;
	cout << "Bounding box: \t" << "---" << endl;
	cout << "Ocupacion: \t" << "----" << endl;
	cout << "Ocup. Convexa: \t" << "---" << endl;
	cout << "Solidez: \t" << "----" << endl;
	cout << "Descriptores de fourier" << "-----" << endl;


}