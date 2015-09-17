#include "algoritmos.hpp"

void rellenaVector(vector <int> &v, const int nEle){
  //Colocamos la semilla con el tiempo actual
  for(int i=0; i<nEle; i++){
    //Ahora rellenamos el vector con numeros aleatorios hasta 9999
    v.push_back(rand()%10000);
  }

}

void ordenacionBurbuja(vector <int> &v){
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

}

void muestraVector(vector<int> &v){

  for(int i=0; i<v.size(); i++){
    cout << v[i] << " ";
  }

  cout << endl;
}

bool estaOrdenado(vector<int> &v){
  for(int i=0; i<v.size()-1; i++){
    assert(v[i]<v[i+1]);
  }
  return(true);
}
