#include "funciones.hpp"


int main(){

	int reinas;
	int contador=0; //Almacenara el numero de soluciones de las reinas
	remove("solucion.txt");

	cout << "Introduce el numero de reinas: ";
	cin >> reinas;

	nReinas(reinas, contador);

	cout << "El numero de soluciones obtenidas es: " << contador << endl;
	
}