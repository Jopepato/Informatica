#include "funciones.hpp"


int main(){
	int maximo=0;
	int minimo=99999;
	int nEle;
	int llamadas=0;
	vector<int> v;

	cout << "Introduce el numero de elementos: ";
	cin >> nEle;

	rellenaVector(v, nEle);
	muestraVector(v);
	minimoMaximo(v, nEle, 1, nEle, maximo, minimo, llamadas);

	cout << endl << "El maximo es: " << maximo << endl;
	cout << "El minimo es: " << minimo << endl;
	cout << "El numero de llamadas del recusivo: " << llamadas << endl;

	return 0;
}