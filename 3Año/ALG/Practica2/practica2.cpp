#include "funciones.hpp"
#include "matriz.hpp"
#include "ClaseTiempo.hpp"

//Aqui haremos lo de las matrices recursivas e iterativas
int main(){
	int n,a,b;
	double det;

	Clock detIterat;
	Clock detRecur;
	
	cout << "Introduce la dimension de la matriz: ";
	cin >> n;
	//Declaramos la matriz
	Matriz<int> m(n,n);
	cout << "Introduce el numero minimo del aleatorio: ";
	cin >> a;
	cout << "Introduce el numero maximo del aleatorio: ";
	cin >> b;

	rellenaMatriz(m,n,n,a,b);
	m.verMatriz();

	//Calculamos el determinante recursivo
	det = determRecursivo(m, n);

	cout << "El determinante es: " << det << endl;

return 0;
}
