#include "funciones.hpp"
#include "matriz.hpp"
#include "ClaseTiempo.hpp"
#include "estimaciones.hpp"

//Aqui haremos lo de las matrices recursivas e iterativas
int main(int argc, char ** argv){

	//Comprobamos que se han introducido todos los parametros pedido
	if(argc!=5){
		cout << "Numero de parametros introducidos incorrectos" << endl;
		exit(-1);
	}

	int minNivel, maxNivel, incremento, repeticion;
	int n,a,b;
	double det;
	vector<int> vectTiempoMedRecur;
	vector<int> vectTiempoMedIterat;
	vector<int> auxVRecur, auxVIter;
	vector<int> muestras;
	double tiempo=0;
	//double tiempoTotalRecur=0.0;

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

	//Hacemos el bucle con las repeticiones
	for(int i=minNivel; i<=maxNivel; i+=incremento){
		Matriz<int> auxM(i,i);
		for(int j=0; j<repeticion; j++){
			//Comprobamos por recursivo
			rellenaMatriz(auxM,i,i,a,b);
			auxM.verMatriz();

			relojRecur.start();
			determRecursivo(auxM,i);
			relojRecur.stop();
			tiempo = relojRecur.elapsed();
			auxVRecur.push_back(tiempo);
			
			//Cogemos el tiempo del iterativo

			relojIterat.start();
			determIterativo(auxM, i);
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
	//Calculamos el determinante recursivo
	//Mostramos el vector de tiempos, junto con el vector de muestras
	muestraVector(muestras);
	muestraVector(vectTiempoMedRecur);
	muestraVector(vectTiempoMedIterat);


return 0;
}
