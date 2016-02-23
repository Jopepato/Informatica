#include "funciones.hpp"

bool lugar(int k, int* x){
	for(int i=1; i<k; i++){
		if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k)){
			return false;
		}
	}

	return true;
}

void nReinas(int n, int &contador){

	int * solucion;
	solucion = (int *)malloc((n+1)*sizeof(int));
	solucion[1]=0;
	int k=1;

	while(k>0){
		solucion[k] = solucion[k]+1;
		while(solucion[k]<=n && lugar(k, solucion)==false){
			solucion[k] = solucion[k]+1;
		}
		if(solucion[k]<=n){
			if(k==(n)){
				//Tenemos la solucion
				escribirSolucion(solucion, n);
				contador++;
			}else{
				k = k+1;
				solucion[k]=0;
			}
		}else{
			k = k-1;
		}
	}
}


void escribirSolucion(int* x, int n){
	//Guarda la solucion en un fichero
	fstream file;
	file.open("solucion.txt",  std::fstream::out | std::fstream::app);
	for(int i=1; i<=n; i++){
		file << x[i] << " ";
	}
	file << "\n";
	file.close();
}