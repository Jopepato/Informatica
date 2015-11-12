#include "funciones.hpp"


bool estaOrdenadoDec(vector<int> v){
	//Para comprobar si el vector esta ordenado de mayor a menor
	for(unsigned int i=0; i<v.size(); i++){
		if(v[i]<v[i+1])
			return false;
	}
	return true;
}

void muestraSolucion(vector<int> monedas, vector<int> solucion){

	/*
	//Mostramos el vector solucion
	for(unsigned int i=0; i<solucion.size(); i++){
		cout << solucion[i] << " ";
	}
	cout << endl;
	*/

	int contador=0;
	cout << endl;
	//Recorremos el vector de monedas y vamos mostrando las ocurrencias de cada uno en el otro vector
	for(unsigned int i=0; i<monedas.size(); i++){
		for(unsigned int j=0; j<solucion.size(); j++){
			if(solucion[j]==monedas[i]){
				contador++;
			}
		}
	//Mostramos las ocurrencias y si son billetes o monedas de centimos
	if(monedas[i]/100 >0){
		//Euros
		cout << "\t" << monedas[i]/100 << " euros: " << contador << endl;
	}else{
		//Centimos
		cout << "\t" << monedas[i] << " centimos: " << contador << endl;
	}

	contador=0;
	}
}


bool encuentraCambioVoraz(vector<int> monedas, vector<int> &solucion,const int &dinero){

//Limpiamos el vector solucion
//El vector monedas tiene que estar ordenado de menor a mayor
int suma = 0;
solucion.clear();
bool salir=false;
unsigned int i;

	while(suma!=dinero){

		for(i=0; i<monedas.size(); i++){
			//Coge el numero mas alto y se sale del for
			if((monedas[i]+suma <= dinero) && !salir){
				suma = suma + monedas[i];
				solucion.push_back(monedas[i]);
				salir = true;
			}
		}

		if(i==monedas.size() && salir==false){
			//No ha encontrado una solución exacta
			return false;
		}

		salir = false;

	}

	return true;
}


bool encuentraCambioDinamico(vector<int> monedas, int &dinero, int ** matrizSolucion){

	//Comenzamos el algoritmo
	for(int i=0; i<monedas.size(); i++){
		matrizSolucion[i][0] = 0;
	}

	for(int i=1; i<monedas.size(); i++){
		for(int j=0; j<dinero; j++){
			if(i==j && j<monedas[i]){
				matrizSolucion[i][j] = INFINITY;
			}else{

			}if(j<monedas[i]){
				matrizSolucion[i][j] = matrizSolucion[i-1][j];
			}else{
				matrizSolucion[i][j] = minimo(matrizSolucion[i-1][j], matrizSolucion[i][j-monedas[i]]);
			}
		}
	}

	return true;
}


int minimo(int a1, int a2){
	if(a1<a2){
		return a1;
	}else{
		return a2;
	}
}