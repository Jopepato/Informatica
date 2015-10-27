#include "matriz.hpp"
#include "funciones.hpp"


int main(){



	Matriz<double> matriz(4,4);
	double aux=0.0;

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout << i <<", " << j << ": ";
			cin >> aux;
			matriz.elemento(4,4,aux);
		}
	}

	

}