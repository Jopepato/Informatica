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
	int n,a,b;
	double detR, detIt;
	vector<double> vectTiempoMedRecur;
	vector<double> vectTiempoMedIterat;
	vector<double> auxVRecur, auxVIter;
	vector<double> muestras, muestrasFactorial;
	double tiempo=0;

	//Declaramos las variables de los ajustes
	double a0Recur, a1Recur, r2Recur;
	double a0It, a1It, a2It, a3It, r2It;

	vector<double> tiempoEstimadoRecur, tiempoEstimadoIt;

	Clock relojIterat;
	Clock relojRecur;
	
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
		
		for(int j=0; j<repeticion; j++){
			Matriz<int> auxM(i,i);
			//Comprobamos por recursivo
			rellenaMatriz(auxM,i,i,a,b);
			
			Matriz<int> auxM2(auxM);

			relojRecur.start();
			detR = determRecursivo(auxM,i);
			relojRecur.stop();
			tiempo = relojRecur.elapsed();
			auxVRecur.push_back(tiempo);
			
			//Cogemos el tiempo del iterativo
			/*
			relojIterat.start();
			detIt = determIterativo(auxM, i);
			relojIterat.stop();
			tiempo = relojIterat.elapsed();
			auxVIter.push_back(tiempo);
			*/
			

		}
		vectTiempoMedRecur.push_back(mediaVector(auxVRecur));
		//vectTiempoMedIterat.push_back(mediaVector(auxVIter));
		auxVRecur.clear();
		auxVIter.clear();
		muestras.push_back(i);
		

	}
	//Calculamos el determinante recursivo
	//Mostramos el vector de tiempos, junto con el vector de muestras
	muestraVector(muestras);
	muestraVector(vectTiempoMedRecur);
	//muestraVector(vectTiempoMedIterat);

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
	cout << "Coeficiente de asimetria: " << r2Recur << endl;

	cout << "Vectorres estimados: " << endl;
	cout << "Recursvo: " << endl;
	muestraVector(tiempoEstimadoRecur);




	//Guardamos las cosas en un fichero

	guardarTiempos(muestras, vectTiempoMedIterat, tiempoEstimadoIt, vectTiempoMedRecur, tiempoEstimadoRecur, "Datos.txt");


return 0;
}
