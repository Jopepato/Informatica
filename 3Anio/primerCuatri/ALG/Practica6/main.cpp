#include "funciones.hpp"
#include "tablero.hpp"


int main(){

	int reinas;
	int contador=0; //Almacenara el numero de soluciones de las reinas
	char opcion;
	//Guarda las soluciones en un fichero
	remove("solucion.txt");

	cout << "Introduce el numero de reinas: ";
	cin >> reinas;

	nReinas(reinas, contador);

	tablero solucion(reinas, contador);
	solucion.leeFichero("solucion.txt");

	cout << "El numero de soluciones obtenidas es: " << contador << endl;
	cout << "Soluciones guardadas a fichero" << endl;

	cout << "Desea mostrar las soluciones por pantalla (S/n): ";
	cin >> opcion;

	if(opcion == 'S'){
		//Muestra
		solucion.muestraTableros();
	}
	
	return 1;
}