#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "estimaciones.hpp"
#include "matriz.hpp"
#include "ClaseTiempo.hpp"



//Aqui haremos lo de las matrices recursivas e iterativas
int main(int argc, char ** argv){

	//Comprobamos que se han introducido todos los parametros pedido
	if(argc!=5){
		cout << "Numero de parametros introducidos incorrectos" << endl;
		exit(-1);
	}

	int minNivel, maxNivel, incremento, repeticion;
	int a,b;
	vector<double> vectTiempoMedRecur;
	vector<double> vectTiempoMedIterat;
	vector<double> auxVRecur, auxVIter;
	vector<double> muestras, muestrasFactorial;
	double tiempo=0.0;
	//double detR=0.0, detI=0.0;

	//Declaramos las variables de los ajustes
	double a0Recur, a1Recur, r2Recur;
	double a0It, a1It, a2It, a3It, r2It;

	vector<double> tiempoEstimadoRecur, tiempoEstimadoIt;

	Clock reloj;
	
	//Pasamos los parametros de comandos a las variables
	minNivel = atoi(argv[1]);
	maxNivel = atoi(argv[2]);
	incremento = atoi(argv[3]);
	repeticion = atoi(argv[4]);

	cout << "Introduce el numero minimo del aleatorio: ";
	cin >> a;
	cout << "Introduce el numero maximo del aleatorio: ";
	cin >> b;

	//Establecemos la semilla
	srand(time(NULL));
	
	
	//Hacemos el bucle con las repeticiones
	for(int i=minNivel; i<=maxNivel; i+=incremento){
		
		cout << "Orden: " <<  i << endl << endl;
		for(int j=0; j<repeticion; j++){
			Matriz<double> auxM(i,i);
			
			//Comprobamos por recursivo
			rellenaMatriz(auxM,i,i,a,b);

			Matriz<double> aux2(auxM);
			
			reloj.start();
			determRecursivo(auxM);
			reloj.stop();
			tiempo = reloj.elapsed();
			auxVRecur.push_back(tiempo);
			
			//Cogemos el tiempo del iterativo
			
			reloj.start();
			determIterativo(aux2);
			reloj.stop();
			tiempo = reloj.elapsed();
			auxVIter.push_back(tiempo);


		}
		vectTiempoMedRecur.push_back(mediaVector(auxVRecur));
		vectTiempoMedIterat.push_back(mediaVector(auxVIter));
		//Mostramos el tiempo medio junto con el nivel
		cout << "Tiempo medio recursivo: " << mediaVector(auxVRecur) << endl;
		cout << "Tiempo medio iterativo: " << mediaVector(auxVIter) << endl;

		auxVRecur.clear();
		auxVIter.clear();
		muestras.push_back(i);
		cout << endl;
	}
	

	//Mostramos el vector de tiempos, junto con el vector de muestras
	cout << "Vector de muestras: " << endl;
	muestraVector(muestras);
	cout << "Vector de tiempos medios recursivos: " << endl;
	muestraVector(vectTiempoMedRecur);
	cout << "Vector de tiempos medios iterativos: " << endl;
	muestraVector(vectTiempoMedIterat);


	vectorAFactorial(muestras, muestrasFactorial);


	//Una vez tenemos los vectores con los tiempos y el vector de muestras podemos calcular los ajustes


	calcularAjusteRecursivo(muestrasFactorial, vectTiempoMedRecur, a0Recur, a1Recur);
	calcularAjusteIterativo(muestras, vectTiempoMedIterat, a0It, a1It, a2It, a3It);



	//Calculamos los tiempos estimados y el r2
	calcularTiemposEstimadosRecursivo(muestrasFactorial, vectTiempoMedRecur, tiempoEstimadoRecur, a0Recur, a1Recur, r2Recur);
	calcularTiemposEstimadosIterativo(muestras, vectTiempoMedIterat, tiempoEstimadoIt, a0It, a1It, a2It, a3It, r2It);

	//Mostramos la ecuacion
	cout << "Ecuacion para el recursivo: " << endl;
	cout << a1Recur << "x! + " << a0Recur << endl;
	cout << "Coeficiente de asimetria: " << r2Recur << endl << endl;


	cout << "Ecuacion para el itearativo: " << endl;
	cout << a3It << "x³ + " << a2It <<"x² + " << a1It << "x + " << a0It <<endl;
	cout << "Coeficiente de asimetria: " << r2It << endl << endl;

	cout << "Vectores estimados: " << endl;
	cout << "Recursivo: " << endl;
	muestraVector(tiempoEstimadoRecur);
	cout << "Iterativo: " << endl;
	muestraVector(tiempoEstimadoIt);

	cout << endl << endl;




	//Guardamos las cosas en un fichero


	cout << "Tiempos guardados en fichero" << endl;
	guardarTiempos(muestras, vectTiempoMedIterat, tiempoEstimadoIt, vectTiempoMedRecur, tiempoEstimadoRecur, "Datos.txt");


return 0;
}
