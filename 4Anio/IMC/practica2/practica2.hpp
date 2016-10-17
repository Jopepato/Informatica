#include <iostream>

using namespace std;

void ayuda(){
	//Función que nos muestra la ayuda con los parámetros cuando fallamos
	cout << "Los parametros para este programa son: " << endl;
	cout << "-t: Fichero con los datos de entrenamiento \t Obligatorio" << endl;
	cout << "-T: Fichero con los datos de test \t Obligatorio" << endl;
	cout << "-i: Número de iteraciones \t Opcional=1000" << endl;
	cout << "-l: Número de capas ocultas \t Opcional=1" << endl;
	cout << "-h: Número de neuronas en capa oculta \t Opcional=5" << endl;
	cout << "-e: Valor del parámetro eta \t Opcional=0.1" << endl;
	cout << "-m: Valor del parámetro mu\t Opcional=0.9" << endl;
	cout << "-b: Uso de sesgo\t Opcional=Falso" << endl;
}