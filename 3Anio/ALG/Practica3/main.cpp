#include "funciones.hpp"


int main(){
	int maximo;
	int minimo;
	int nEle;
	int llamadas=0;
	vector<int> v;

	cout << "Introduce el numero de elementos: ";
	cin >> nEle;

	srand(time(NULL));

	rellenaVector(v, nEle);
	muestraVector(v);
	minimoMaximo(v, nEle-1, 0, nEle-1, maximo, minimo, llamadas);

	cout << endl << "El maximo es: " << maximo << endl;
	cout << "El minimo es: " << minimo << endl;
	cout << "El numero de llamadas del recusivo: " << llamadas << endl;

	return 0;
}