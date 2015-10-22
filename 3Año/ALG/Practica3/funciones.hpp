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
}

template <class T>
bool maximoMinimoRecur(const vector<T> &v, int &max, int &min, int &llamadas, int i){
	if(i==v.size()){
		return true;
	}else{
		if(v[i]>max){
			max = v[i];
		}
		if(v[i]<min){
			min = v[i];
		}
		llamadas++;
		
		maximoMinimoRecur(v, max, min, llamadas, i+1);
	}
	return false;
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
		if(i ==j-1){
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
			max = Maximo(maximo1, maximo2);
			min = Minimo(minimo1, minimo2);

		}
	}
}


#endif