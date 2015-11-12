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
//c1.muestraMonedas();


cout << "Introduce el numero de euros: ";
cin >> euros;
euros = euros*100;
cout << "Introduce el numero de centimos: ";
cin >> centimos;
dinero = euros+centimos;

//Hacemos la matriz
//Matriz<int> solucionDin(c1.getNumeroMonedas(),dinero);
int ** solucionDin;
int columnas = dinero+1;
//Reservo memoria
solucionDin = (int**)malloc(c1.getNumeroMonedas()*sizeof(int*));
for(int i=0; i<c1.getNumeroMonedas(); i++){
	solucionDin[i] = (int *)malloc(columnas*sizeof(int));
}


//Metemos el dinero en centimos en el cambio

//Suponemos que el vector de monedas esta ordenado de forma decreciente
	if(encuentraCambioVoraz(c1.getMonedas(), solucion, dinero)){
		cout << "Se ha encontrado una solucion: " << endl;
	}else{
		cout << "No se ha encontrado una solucion" << endl;
		cout << "Pero la solucion aproximada es: " << endl;
	}

//Tenemos que ordenar el vector de monedas de manera ascendente para encontrar la solucion dinamica
c1.ordenaMonedasAsc();

c1.muestraMonedas();
//Hacemos el cambio dinamico
encuentraCambioDinamico(c1.getMonedas(), columnas, solucionDin);
muestraMatriz(solucionDin,c1.getMonedas(), c1.getNumeroMonedas(), columnas);
solucion.clear();
rellenaSolucionDinamica(solucionDin, c1.getNumeroMonedas(),columnas, c1.getMonedas(), solucion);

cout << "hola" << endl;
//Mostamos la solución tanto si es aproximada como si no lo es
muestraSolucion(c1.getMonedas(), solucion);



cout << endl;



}
