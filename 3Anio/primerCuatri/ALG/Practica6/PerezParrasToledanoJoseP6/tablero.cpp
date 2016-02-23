#include "tablero.hpp"


void tablero::leeFichero(const string &nombreFichero){
	//Leeremos el fichero y lo pasamos al vector
	ifstream fichero;
	fichero.open(nombreFichero.c_str());
	int aux;
	vector<int> vectorAux;

	if(!fichero.is_open()){
		cout << "No se pudo abrir el fichero" << endl;
		exit(-1);
	}

	for(int i=0; i<getSoluciones(); i++){
		for(int j=0; j<getReinas(); j++){
			fichero >> aux;
			vectorAux.push_back(aux);
		}
		tablero_.push_back(vectorAux);
		vectorAux.clear();

	}

	fichero.close();
}



void tablero::muestraVectores(){

	//Mostramos los vectores por pantalla
	for(int i=0; i<getSoluciones(); i++){
		cout << "Solucion " << i << endl;
		for(int j=0; j<getReinas(); j++){
			cout << tablero_[i][j] << " ";
		}
		cout << endl;
	}

}

void tablero::muestraTableros(){
	//Para cada solucion tenemos que mostrar un tablero

	for(int i=0; i<getSoluciones(); i++){
		//Tenemos que mostrar todas estas soluciones

		cout << "Solucion " << i+1 << endl;

		for(int j=0; j<getReinas(); j++){
			for(int k=0; k<getReinas(); k++){
				if(tablero_[i][j] == k+1){
					cout << "[x]" << " ";
				}else{
					cout << "[ ]" << " ";
				}
			}
			cout << endl;
		}
		cout << endl;

	}
}