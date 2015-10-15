#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "matriz.hpp"
using namespace std;

void reservaMemoria(int **&m, int n){
	m = (int**)malloc(n*sizeof(int*));
	for(int i=0; i<n; i++){
		m[i] = (int*)malloc(n*sizeof(int));
	}
}

double determRecursivo(int **a,int n) {
  int det=0, p, h, k, i, j, **temp;
  reservaMemoria(temp, n);

  if(n==1) {
    return a[0][0];
  } else if(n==2) {
    det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
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
          temp[h][k] = a[i][j];
          k++;
          if(k==n-1) {
            h++;
            k = 0;
          }
        }
      }
      det=det+a[0][p]*pow(-1,p)*determ(temp,n-1);
    }
    return det;
  }
}
