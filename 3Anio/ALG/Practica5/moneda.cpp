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
	if(!fichero.is_open()){
		cout << "Error abriendo fichero 'monedas.txt'" << endl;
		exit(-1);
	}

	while(!fichero.eof()){
		fichero >> aux;
		monedas_.push_back(aux);
	}
	monedas_.pop_back();
	fichero.close();

	//Ordenamos el vector
	//Primero vemos si necesitamos ordenar
	if(!estaOrdenadoDesc(monedas_)){
		ordenaMonedasDesc();
	}
	

};

//Para ordenar descendentemente con el qsort
bool descendente(int i, int j){
	return i>j;
};

void moneda::ordenaMonedasDesc(){
	//Si el fichero que leemos no esta ordenado de mayor a menor lo ordenamos
  /*int aux;
  for(unsigned int i=0; i<=monedas_.size(); i++){
    for(unsigned int j=0; j<monedas_.size(); j++){
      if(monedas_[j]<monedas_[j+1]){
        aux = monedas_[j];
        monedas_[j] = monedas_[j+1];
        monedas_[j+1] = aux;
      }//finsi
    }//finpara J
  }//finpara I
  */

  //Para realizarlo de una forma mas eficiente se puede usar el sort
  sort(monedas_.begin(), monedas_.end(), descendente);

};

void moneda::ordenaMonedasAsc(){
 /* int aux;
  for(unsigned int i=0; i<=monedas_.size(); i++){
    for(unsigned int j=0; j<monedas_.size()-1; j++){
      if(monedas_[j]>monedas_[j+1]){
        aux = monedas_[j];
        monedas_[j] = monedas_[j+1];
        monedas_[j+1] = aux;
      }//finsi
    }//finpara J
  }//finpara I
 */

  //De una forma mas eficiente seria usando el qsort
  sort(monedas_.begin(), monedas_.end());
  
};