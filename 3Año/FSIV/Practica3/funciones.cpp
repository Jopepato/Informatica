#include "funciones.hpp"

void help(){

	cout << "Ayuda con los comandos: " << endl;
	cout << "-h: Muestra la ayuda del programa" << endl;
	cout << "-i nombreImagen: Imagen que se va a cargar para el programa" << endl;
	cout << "-m 0 o 1: Método que se va a usar local(0), global(1)" << endl;
	cout << "-r radio: Radio del elemento estructural" << endl;
	cout << "-c umbral: Valor usado para obtener el umbral local de cada pixel" << endl;
	cout << "-o nombreImagenSalida: Imagen de salida segmentada" << endl;
}