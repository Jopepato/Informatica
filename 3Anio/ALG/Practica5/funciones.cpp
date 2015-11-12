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

	int aux;
	//Comenzamos el algoritmo
	for(unsigned int i=0; i<monedas.size(); i++){
		matrizSolucion[i][0] = 0;
	}

	for(unsigned int i=0; i<monedas.size(); i++){
		for(int j=0; j<dinero; j++){
			if(i==0 && j<monedas[i]){
				matrizSolucion[i][j] = numeric_limits<int>::infinity();
			}else{
				if(i==0){
				matrizSolucion[i][j] = 1 + matrizSolucion[i][j-monedas[0]];
				}else{
					if(j<monedas[i]){
						matrizSolucion[i][j] = matrizSolucion[i-1][j];
					}else{
						aux = minimo(matrizSolucion[i-1][j], 1+matrizSolucion[i][j-monedas[i]]);
						matrizSolucion[i][j] = aux;
					}
				}
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

void muestraMatriz(int ** matriz,vector<int> monedas, int fil, int col){
	for(int i=0; i<fil; i++){
		cout << monedas[i] << " ------>   ";
		for(int j=0; j<col; j++){
			cout << matriz[i][j] << " ";
		}
			cout << endl;
	}
}

bool rellenaSolucionDinamica(int ** matriz, int fil, int col, vector<int> monedas, vector<int> &solucion){

	//Aqui vamos a rellenar el vector de soluciones
	int i=fil-1, j=col-1;
	while(j!=0 && i>-1){
		if(i!=0){
			if(matriz[i][j] == matriz[i-1][j]){
				i--;
			}else{
				if(matriz[i][j-monedas[i]]+1 == matriz[i][j]){
					solucion.push_back(monedas[i]);
					j = j-monedas[i];
				}
			}
		}else{
			if(matriz[i][j-monedas[i]]+1 == matriz[i][j]){
				solucion.push_back(monedas[i]);
				j = j-monedas[i];
			}else{
				//Aqui entra cuando no hay nada mas para comparar ya que no encuentra la solucion optima
				//Sin este apartado se quedaria en un bucle infinito
				return false;
			}
		}
		
	}

	return true;

};
