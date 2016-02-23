#include "funciones.hpp"
#include "moneda.hpp"

int main(){


moneda c1;
//int euros;
//int centimos;
//int dinero;
char opcion;
bool vflag;
int columnas;
string nombreFichero = "monedas.txt";
string nombreFicheroTiempos = "tiempos.txt";
vector<int> solucion;
vector<double> tiempoVoraz;
double tiempoVorazTotal=0;
vector<double> tiempoDinamico;
double tiempoDinamicoTotal=0;
vector<int> muestras;
Clock reloj;
int repeticiones;
srand(time(NULL));
int incremento;
int numMuestra=0;

//Rellenamos el vector de monedas
c1.leerFichero(nombreFichero);


cout << "Introduce el numero de repeticiones para la media: ";
cin >> repeticiones;

cout << "Introduce el incremento: ";
cin >> incremento;

cout << "¿Desea mostrar los tiempos de cada iteracion por pantalla? (S/n): ";
cin >> opcion;

	if(opcion=='S'){
		vflag=true;
	}else{
		vflag=false;
	}

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


for(int i=50000; i<=100000; i=i+incremento){
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
		//Hacemos el cambio dinamico
		reloj.start();
		encuentraCambioDinamico(c1.getMonedas(), columnas, solucionDin);
		reloj.stop();
		tiempoDinamicoTotal = tiempoDinamicoTotal + reloj.elapsed();

		//Y liberamos la memoria de la matriz
		for(int k=0; k<c1.getNumeroMonedas(); k++){
			free(solucionDin[k]);
		}
		free(solucionDin);

		//Volvemos a ordenar para el metodo voraz
		c1.ordenaMonedasDesc();
	}

	tiempoVoraz.push_back(tiempoVorazTotal/repeticiones);
	tiempoDinamico.push_back(tiempoDinamicoTotal/repeticiones);
	muestras.push_back(i);
	//Lo mostramos por pantalla
	if(vflag){
		cout << "Muestra: " << i << endl;
		cout << "Tiempo voraz: " << tiempoVoraz[numMuestra] << endl;
		cout << "Tiempo dinamico: " << tiempoDinamico[numMuestra] << endl;
	}
	numMuestra++;
}


	//Guardamos los tiempos en el fichero
	guardaTiempos(muestras, tiempoVoraz, tiempoDinamico, nombreFicheroTiempos);

	cout << endl << "Tiempos pasados a fichero" << endl;


/******************************************************************************************************************
Para mostrar la solucion por pantalla del algoritmo dinamico, solucion obtenida por la matriz del numero de monedas
Habria que dar valor a la variable "dinero"
*******************************************************************************************************************/
/*
//Tenemos que ordenar el vector de monedas de manera ascendente para encontrar la solucion dinamica
c1.ordenaMonedasAsc();

c1.muestraMonedas();
columnas = dinero +1;
//Hacemos el cambio dinamico
encuentraCambioDinamico(c1.getMonedas(), columnas, solucionDin);
muestraMatriz(solucionDin,c1.getMonedas(), c1.getNumeroMonedas(), columnas);
solucion.clear();
rellenaSolucionDinamica(solucionDin, c1.getNumeroMonedas(),columnas, c1.getMonedas(), solucion);

//Mostamos la solución tanto si es aproximada como si no lo es
muestraSolucion(c1.getMonedas(), solucion);

*/

}
