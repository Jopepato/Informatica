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