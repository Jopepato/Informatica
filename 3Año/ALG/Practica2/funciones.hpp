#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "matriz.hpp"
using namespace std;

template <class T>
inline void rellenaMatriz(Matriz<T> &m, int f, int c, int a, int b){
		//Rellenaremos la matriz con numeros aleatorios comprendidos entre a y b
	srand(time(NULL));
	for(int i=1; i<=c; i++){
		for(int j=1; j<=f; j++){
			int aux = rand()%(b-a);
			aux = aux +a;
			m.elemento(i, j, aux);
		}
	}
	//Con esto ya tenemos la matriz rellena de numeros aleatorios entre a y b
};


template <class T>
double determRecursivo(Matriz<T> m,int n) {
  double det=0, p=0, h=0, k=0, i=0, j=0;
  Matriz<T> temp(n,n);

  if(n==1) {
    return m.elemento(1,1);
  } else if(n==2) {
    det=(m.elemento(1,1)*m.elemento(2,2)-m.elemento(1,2)*m.elemento(2,1));
    return det;
  } else {
    for(p=1;p<=n;p++) {
      h = 1;
      k = 1;
      for(i=2;i<=n;i++) {
        for( j=1;j<=n;j++) {
          if(j==p) {
            continue;
          }
          temp.elemento(h,k,m.elemento(i,j));
          k++;
          if(k==n) {
            h++;
            k = 1;
          }
        }
      }
      det=det+m.elemento(1,p)*pow(-1,p)*determRecursivo(temp,n-1);
    }
    return (-1)*det;
  }
}

template <class T>
double determIterativo(Matriz <T> &a, const int &n) {

			// Algoritmo para la eliminación simple de Gauss

		    double det;
		    T aux;
		    T factor;
		 
		    for (int k = 1; k < n ; k++) {
		        for (int i = k+1; i <= n;  i++) {
		            factor = a.elemento(i,k)/a.elemento(k,k);
		            for (int j = k+1; j < n+1 ; j++) {
		            	aux=a.elemento(i,j) - factor * a.elemento(k,j);
		                a.elemento(i,j, aux);
		            }
		        }
		    }

		// Cálculo del determinante
		    det = 1;
		    for (int i = 1; i <= n; i++) {
		        det = det * a.elemento(i,i);
		    }

		    return det;
		}


//Funciones genericas

template <class T>
double mediaVector(vector<T> &v){
	//Hace la media de un vector V
	double total=0.0, media=0.0;
	for(int i=0; i<v.size(); i++){
		total = total+v[i];
	}
	media = total/v.size();
	return media;
}

template <class T>
double varianzaVector(vector<T> &v, T media){
	//Sumatorio del elemento menos la media al cuadrado
	double varianza=0.0;
	for(int i=0; i<v.size(); i++){
		varianza = varianza + pow(v[i]-media,2);
	}

	//Dividimos entre el numero de elementos
	varianza = varianza/v.size();
	return varianza;
}



template <class T>
void muestraVector(vector<T> &v){
	//muestra el vector entero
	
	for(int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

template <class T>
double sumatorioVector(vector<T> &v){
	//Sumatorio de un vector
	double suma=0.0;
	
	for(int i=0; i<v.size(); i++){
		suma += v[i];
	}
	return suma;
}

template <class T>
double sumatorio2Vector(const vector<T> &v){
	double suma2=0.0;
	
	for(int i=0; i<v.size(); i++){
		suma2 += pow(v[i],2);
	}
	return suma2;
}

template <class T>
double sumatorio3Vector(const vector<T> &v){
	double suma3=0.0;
	
	for(int i=0; i<v.size(); i++){
		suma3 += pow(v[i],3);
	}
	return suma3;
}

template <class T>
double sumatorio4Vector(const vector<T> &v){
	double suma4=0.0;

	for(int i=0; i<v.size(); i++){
		suma4 += pow(v[i],4);
	}
	return suma4;
}

template <class T>
double sumatorio5Vector(const vector<T> &v){
	double suma5=0.0;
	for(int i=0; i<v.size(); i++){
		suma5 += pow(v[i],5);
	}
	return suma5;

}

template <class T>
double sumatorio6Vector(const vector<T> &v){
	double suma6=0.0;
	
	for(int i=0; i<v.size(); i++){
		suma6 += pow(v[i], 6);
	}
	return suma6;
}

template <class T>
double sumatorioxyVector(const vector<T> &x,const vector<T> &y){
	double sumaxy=0.0;
	//Los dos vectores deben de ser del mismo tamaño
	
	for(int i=0; i<x.size(); i++){
		sumaxy += x[i]*y[i];
	}
	return sumaxy;
}

template <class T>
double sumatoriox2yVector(const vector<T> &x,const  vector<T> &y){
	double sumax2y =0.0;

	for(int i=0; i<x.size(); i++){
		sumax2y += pow(x[i], 2)*y[i];
	}
	return sumax2y;
}

template <class T>
double sumatoriox3yVector(const vector<T> &x,const vector<T> &y){
	double sumax3y=0.0;

	for(int i=0; i<x.size(); i++){
		sumax3y += pow(x[i],3) *y[i];
	}
	return sumax3y;
}

template <class T>
void vectorAFactorial(vector<T> &x, vector<T> &y){
	//Recorremos el vector y pasamos a otro sus
	for(int i=0; i<x.size(); i++){
		y.push_back(factorial(x[i]));
	}
}


double factorial(double num){
	double factorial=1;
	for(int i=num; i>0; i--){
		factorial = factorial*i;
	}
	return factorial;
}

#endif
