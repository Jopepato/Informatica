#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
template <class T>
void rellenaVector(vector <T> &v, int nEle){
  //Colocamos la semilla con el tiempo actual
  //Limpiamos el vector por si ya estaba relleno
  v.clear();
  for(int i=0; i<nEle; i++){
    //Ahora rellenamos el vector con numeros aleatorios hasta 9999
    v.push_back(rand()%10000);
  }
}

template <class T>
void muestraVector(const vector<T> &v){
	//Mostramos el vector
	for(int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

template <class T>
T Minimo(T min1, T min2){
	if(min1<min2){
		return min1;
	}else{
		return min2;
	}
}

template <class T>
T Maximo(T max1, T max2){
	if(max1>max2){
		return max1;
	}else{
		return max2;
	}
}


template <class T>
void minimoMaximo(vector<T> &v, int n, int i, int j, int &max, int &min, int &llamadas){
	int mitad;
	T maximo1, minimo1, maximo2, minimo2;
	
	if(i==j){
		max = v[i];
		min = v[i];
	}else{
		if(i ==(j-1)){
			if(v[i]<v[j]){
				max = v[j];
				min = v[i];
			}else{
				max = v[i];
				min = v[j];
			}
		}else{
			mitad = (i+j)/2;
			llamadas++;
			minimoMaximo(v,n,i,mitad,maximo1,minimo1, llamadas);
			llamadas++;
			minimoMaximo(v,n,mitad+1,j,maximo2, minimo2, llamadas);
			//muestraVector(v);
			max = Maximo(maximo1, maximo2);
			min = Minimo(minimo1, minimo2);
		}
	}
}


template <class T>
bool estaOrdenado(vector<T> &v){
  for(unsigned int i=0; i<v.size()-1; i++){
    assert(v[i]<=v[i+1]);
  }
  return(true);
}

template <class T>
void ordenacionBurbuja(vector <T> &v){
  int aux;
  int n = v.size();
  for(int i=0; i<=n; i++){
    for(int j=0; j<n; j++){
      if(v[j]>v[j+1]){
        aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
      }//finsi
    }//finpara J
  }//finpara I
  estaOrdenado(v);
}

template <class T>
void fusionar(vector<T> &u, vector<T> &v, vector<T> &t){
	int i=0, j=0;
	u[u.size()-1] = INFINITY;
	v[v.size()-1] = INFINITY;
	for(int k=0; k<(u.size()+v.size()); k++){
		if(u[i]<v[j]){
			t[k] = u[i];
			i++;
		}else{
			t[k] = v[j];
			j++;
		}
	}
	//Ya se crearia el vector ordenado de la fusion
}

#endif