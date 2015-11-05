#include "funciones.hpp"


int main(){
	int maximo;
	int minimo;
	int nEle;
	int llamadas=0;
	vector<int> v;
	char opcion;

	cout << "Introduce el numero de elementos: ";
	cin >> nEle;

	//Ponemos la semilla a null
	srand(time(NULL));

	rellenaVector(v, nEle);
	cout << "Vector generado." << endl;
	cout << "¿Desea mostrar el vector? (s/n): ";
	cin >> opcion;
	if(opcion == 's' || opcion == 'S'){
		cout << endl;
		muestraVector(v);
	}
	minimoMaximo(v, nEle-1, 0, nEle-1, maximo, minimo, llamadas);

	cout << endl << "El maximo es: " << maximo << endl;
	cout << "El minimo es: " << minimo << endl;
	cout << "El numero de llamadas recursivas: " << llamadas << endl;

	return 0;
}
