#ifndef FUNCIONES2_HPP_
#define FUNCIONES2_HPP_


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