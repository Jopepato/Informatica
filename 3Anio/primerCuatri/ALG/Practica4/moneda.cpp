#include "moneda.hpp"

void moneda::muestraMonedas(){

	//Mostramos el vector de monedas
	for(unsigned int i=0; i<monedas_.size(); i++){
		cout << monedas_[i] << " ";
	}
	cout << endl;
};


void moneda::leerFichero(const string &nombreFichero){

	monedas_.clear();
	fstream fichero;
	fichero.open(nombreFichero.c_str(), fstream::in);
	int aux;

	while(!fichero.eof()){
		fichero >> aux;
		monedas_.push_back(aux);
	}
	monedas_.pop_back();
	fichero.close();

	//Ordenamos el vector
	//Primero vemos si necesitamos ordenar
	if(!estaOrdenadoDec(monedas_)){
		ordenaMonedas();
	}
	

};

void moneda::ordenaMonedas(){
	//Si el fichero que leemos no esta ordenado de mayor a menor lo ordenamos
  int aux;
  for(unsigned int i=0; i<=monedas_.size(); i++){
    for(unsigned int j=0; j<monedas_.size(); j++){
      if(monedas_[j]<monedas_[j+1]){
        aux = monedas_[j];
        monedas_[j] = monedas_[j+1];
        monedas_[j+1] = aux;
      }//finsi
    }//finpara J
  }//finpara I

};


