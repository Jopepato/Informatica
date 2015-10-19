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
	double detR=0.0, detIt=0.0;
	vector<double> vectTiempoMedRecur;
	vector<double> vectTiempoMedIterat;
	vector<double> auxVRecur, auxVIter;
	vector<double> muestras, muestrasFactorial;
	double tiempo=0.0;

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

/*
	cout << "hola" << endl;
	//Vamos a probar a ir tirando para atras y vamos quitando fila y columna
	Matriz<double> mat(maxNivel, maxNivel);
	rellenaMatriz(mat,maxNivel,maxNivel,a,b);
	//Hacemos un doble for
	for(int i=maxNivel; i>=minNivel; i=i-incremento){

		for(int j=0; j<repeticion; j++){

			//Para el tiempo recursivo
			relojRecur.start();
			detR = determRecursivo(mat,i);
			relojRecur.stop();
			tiempo = relojRecur.elapsed();
			auxVRecur.push_back(tiempo);

			//Para el tiempo iterativo
			relojIterat.start();
			detIt = determIterativo(mat, i);
			relojIterat.stop();
			tiempo = relojIterat.elapsed();
			auxVIter.push_back(tiempo);

		}
		vectTiempoMedRecur.push_back(mediaVector(auxVRecur));
		vectTiempoMedIterat.push_back(mediaVector(auxVIter));
		auxVRecur.clear();
		auxVIter.clear();
		mat.eliminarFilaColumna(i,i);
		muestras.push_back(i);

	}
*/


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
			
			relojIterat.start();
			detIt = determIterativo(auxM2, i);
			relojIterat.stop();
			tiempo = relojIterat.elapsed();
			auxVIter.push_back(tiempo);
			
			

		}
		vectTiempoMedRecur.push_back(mediaVector(auxVRecur));
		vectTiempoMedIterat.push_back(mediaVector(auxVIter));
		auxVRecur.clear();
		auxVIter.clear();
		muestras.push_back(i);
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


	cout << "Guardamos los tiempos en fichero" << endl;
	guardarTiempos(muestras, vectTiempoMedIterat, tiempoEstimadoIt, vectTiempoMedRecur, tiempoEstimadoRecur, "Datos.txt");


return 0;
}
