#include "cambio.hpp"

void cambio::getMonedas(){

	//Mostramos el vector de monedas
	for(unsigned int i=0; i<monedas.size(); i++){
		cout << monedas[i] << " ";
	}
	cout << endl;
};

void cambio::getSolucion(){

	/*
	//Mostramos el vector solucion
	for(unsigned int i=0; i<solucion.size(); i++){
		cout << solucion[i] << " ";
	}
	cout << endl;
	*/

	int contador=0;
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
};

void cambio::leerFichero(const string &nombreFichero){

	monedas.clear();
	fstream fichero;
	fichero.open(nombreFichero.c_str(), fstream::in);
	int aux;

	while(!fichero.eof()){
		fichero >> aux;
		monedas.push_back(aux);
	}
	monedas.pop_back();
	fichero.close();

	//Ordenamos el vector
	//Primero vemos si necesitamos ordenar
	if(!estaOrdenadoDec(monedas)){
		cout << "Vector no ordenado, lo ordenamos" << endl;
		ordenaMonedas();
	}
	

};

bool cambio::encuentraSolucion(){

//Limpiamos el vector solucion
//El vector monedas tiene que estar ordenado de menor a mayor
int suma = 0;
solucion.clear();
bool salir=false;
unsigned int i;

	while(suma!=dinero){

		for(i=0; i<monedas.size(); i++){
			if((monedas[i]+suma <= dinero) && !salir){
				suma = suma + monedas[i];
				solucion.push_back(monedas[i]);
				salir = true;
			}
		}

		if(i==monedas.size() && salir==false){
			return false;
		}

		salir = false;

	}

	return true;
}

void cambio::ordenaMonedas(){
	//Si el fichero que leemos no esta ordenado de mayor a menor lo ordenamos
  int aux;
  for(unsigned int i=0; i<=monedas.size(); i++){
    for(unsigned int j=0; j<monedas.size(); j++){
      if(monedas[j]<monedas[j+1]){
        aux = monedas[j];
        monedas[j] = monedas[j+1];
        monedas[j+1] = aux;
      }//finsi
    }//finpara J
  }//finpara I

}


