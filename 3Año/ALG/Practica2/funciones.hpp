#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
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
  int det=0, p, h, k, i, j;
  Matriz<T> temp(n,n);

  if(n==1) {
    return m.elemento(0+1,0+1);
  } else if(n==2) {
    det=(m.elemento(0+1,0+1)*m.elemento(1+1,1+1)-m.elemento(0+1,1+1)*m.elemento(1+1,0+1));
    return det;
  } else {
    for(p=0;p<n;p++) {
      h = 0;
      k = 0;
      for(i=1;i<n;i++) {
        for( j=0;j<n;j++) {
          if(j==p) {
            continue;
          }
          temp.elemento(h+1,k+1,m.elemento(i+1,j+1)+1);
          k++;
          if(k==n-1) {
            h++;
            k = 0;
          }
        }
      }
      det=det+m.elemento(0+1,p+1)*pow(-1,p)*determRecursivo(temp,n-1);
    }
    return det;
  }
}

#endif
