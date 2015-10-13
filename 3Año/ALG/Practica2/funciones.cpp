#include "funciones.hpp"



void rellenaMatriz(Matriz<T> &m, int c, int f, int a, int b){
	//Rellenaremos la matriz con numeros aleatorios comprendidos entre a y b
	srand(time(NULL));
	for(int i=0; i<c; i++){
		for(int j=0; j<f; j++){
			int aux = rand()%(b-a);
			aux = aux +a;
			m[i][j] = aux;
		}
	}
	//Con esto ya tenemos la matriz rellena de numeros aleatorios entre a y b
}

void muestraMatriz(Matriz<T> &m){
	//Aqui mostraremos la matriz
	for(int i=0; i<m.filas(); i++){
		for(int j=0; j<m.columnas(); j++ ){
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}

}
