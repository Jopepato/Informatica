#include "funciones.hpp"


//Aqui haremos lo de las matrices recursivas e iterativas
int main(){
	int f,c,a,b;
	cout << "Introduce el numero de filas: ";
	cin >> f;
	cout << "Introduce el numero de columnas: ";
	cin >> c;
	cout << "Introduce el numero minimo del aleatorio: ";
	cin >> a;
	cout << "Introduce el numero maximo del aleatorio: ";
	cin >> b;

	Matriz<int> matriz(f,c);

	rellenaMatriz(matriz,c,f,a,b);
	muestraMatriz(matriz);

}
