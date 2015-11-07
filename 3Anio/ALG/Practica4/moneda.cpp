#include "moneda.hpp"

void moneda::muestraMonedas(){

	//Mostramos el vector de monedas
	for(unsigned int i=0; i<monedas.size(); i++){
		cout << monedas[i] << " ";
	}
	cout << endl;
};


void moneda::leerFichero(const string &nombreFichero){

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
		ordenaMonedas();
	

};

void moneda::ordenaMonedas(){
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

};


