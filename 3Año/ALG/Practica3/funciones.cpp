#include "funciones.hpp"


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
bool maximoMinimoRecur(const vector<T> &v, int &max, int &min, int &llamadas, int &i){
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
}