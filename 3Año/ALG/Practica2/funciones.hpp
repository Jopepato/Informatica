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

void reservaMemoria(int **&m, int n){
	m = (int**)malloc(n*sizeof(int*));
	for(int i=0; i<n; i++){
		m[i] = (int*)malloc(n*sizeof(int));
	}
}
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
double mediaVector(vector<T> &v){
	//Hace la media de un vector V
	double total=0.0, media=0.0;
	for(int i=0; i<v.size(); i++){
		total = total+v[i];
	}
	media = total/v.size();
	return media;
}

#endif
