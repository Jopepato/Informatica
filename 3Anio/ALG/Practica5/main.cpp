#include "funciones.hpp"
#include "moneda.hpp"

int main(){


moneda c1;
int euros;
int centimos;
int dinero;
int columnas;
string nombreFichero = "monedas.txt";
vector<int> solucion;
vector<float> tiempoVoraz;
float tiempoVorazTotal=0;
vector<float> tiempoDinamico;
float tiempoDinamicoTotal=0;
vector<int> muestras;
Clock reloj;
int repeticiones;
srand(time(NULL));

//Rellenamos el vector de monedas
c1.leerFichero(nombreFichero);


cout << "Introduce el numero de repeticiones para la media:";
cin >> repeticiones;

/*
cout << "Introduce el numero de euros: ";
cin >> euros;
euros = euros*100;
cout << "Introduce el numero de centimos: ";
cin >> centimos;
dinero = euros+centimos;
*/

//Hacemos la matriz
int ** solucionDin;

//Hacemos el bucle para contar los tiempos y almacenar las muestras


for(int i=50000; i<100000; i=i+rand()%100000){
	for(int j=0; j<repeticiones; j++){
		//Reservo memoria
		columnas = i+1;
		solucionDin = (int**)malloc(c1.getNumeroMonedas()*sizeof(int*));
		for(int k=0; k<c1.getNumeroMonedas(); k++){
			solucionDin[k] = (int *)malloc(columnas*sizeof(int));
		}
		//Ya tenemos la matriz reservada

		//Hacemos el cambio voraz
		reloj.start();
		encuentraCambioVoraz(c1.getMonedas(), solucion, i);
		reloj.stop();
		tiempoVorazTotal = tiempoVorazTotal + reloj.elapsed();
		solucion.clear();
		//Nos preparamos para la solucion dinamica
		c1.ordenaMonedasAsc();
		reloj.start();
		encuentraCambioDinamico(c1.getMonedas(), columnas, solucionDin);
		reloj.stop();
		tiempoDinamicoTotal = tiempoDinamicoTotal + reloj.elapsed();

		//Y liberamos la memoria de la matriz
		
		for(int k=0; k<c1.getNumeroMonedas(); k++){
			free(solucionDin[k]);
		}
		free(solucionDin);
		
	}

	tiempoVoraz.push_back(tiempoVorazTotal/repeticiones);
	tiempoDinamico.push_back(tiempoDinamicoTotal/repeticiones);
	muestras.push_back(i);
	//Lo mostramos por pantalla
	cout << "Muestra: " << i << endl;
	cout << "Tiempo voraz: " << tiempoVoraz[i] << endl;
	cout << "Tiempo dinamico: " << tiempoDinamico[i] << endl;
}







/*
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

//Mostamos la solución tanto si es aproximada como si no lo es
muestraSolucion(c1.getMonedas(), solucion);

*/

cout << endl;



}
