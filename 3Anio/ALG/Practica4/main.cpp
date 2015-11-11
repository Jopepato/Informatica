#include "funciones.hpp"
#include "moneda.hpp"

int main(){


moneda c1;
int euros;
int centimos;
int dinero;
string nombreFichero = "monedas.txt";
vector<int> solucion;

//Rellenamos el vector de monedas
c1.leerFichero(nombreFichero);

//Mostramos el vector de monedas
cout << "Sistema monetario: " << endl;
c1.muestraMonedas();


cout << "Introduce el numero de euros: ";
cin >> euros;
euros = euros*100;
cout << "Introduce el numero de centimos: ";
cin >> centimos;
dinero = euros+centimos;

//Metemos el dinero en centimos en el cambio

//Suponemos que el vector de monedas esta ordenado de forma decreciente
	if(encuentraCambio(c1.getMonedas(), solucion, dinero)){
		cout << "Se ha encontrado una solucion: " << endl;
	}else{
		cout << "No se ha encontrado una solucion" << endl;
		cout << "Pero la solucion aproximada es: " << endl;
	}


muestraSolucion(c1.getMonedas(), solucion);

cout << endl;



}
