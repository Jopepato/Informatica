#include "algoritmos.hpp"

void rellenaVector(vector <double> &v, const int nEle){
  //Colocamos la semilla con el tiempo actual
  //Limpiamos el vector por si ya estaba relleno
  v.clear();
  for(int i=0; i<nEle; i++){
    //Ahora rellenamos el vector con numeros aleatorios hasta 9999
    v.push_back(rand()%10000);
  }

}

void ordenacionBurbuja(vector <double> &v){
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

void muestraVector(vector<double> &v){

  for(int i=0; i<v.size(); i++){
    cout << v[i] << " ";
  }

  cout << endl;
}

bool estaOrdenado(vector<double> &v){
  for(int i=0; i<v.size()-1; i++){
    assert(v[i]<=v[i+1]);
  }
  return(true);
}

// A utility function to swap two elements
void swap ( double* a, double* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function is same in both iterative and recursive*/
int partition (vector<double> &arr, int l, int h)
{
    double x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}

/* A[] --> Array to be sorted, l  --> Starting index, h  --> Ending index */
void quickSortIterative (vector<double> &arr, int l, int h)
{
    // Create an auxiliary stack
    int stack[ h - l + 1 ];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[ ++top ] = l;
    stack[ ++top ] = h;

    // Keep popping from stack while is not empty
    while ( top >= 0 )
    {
        // Pop h and l
        h = stack[ top-- ];
        l = stack[ top-- ];

        // Set pivot element at its correct position in sorted array
        int p = partition( arr, l, h );

        // If there are elements on left side of pivot, then push left
        // side to stack
        if ( p-1 > l )
        {
            stack[ ++top ] = l;
            stack[ ++top ] = p - 1;
        }

        // If there are elements on right side of pivot, then push right
        // side to stack
        if ( p+1 < h )
        {
            stack[ ++top ] = p + 1;
            stack[ ++top ] = h;
        }
    }

    estaOrdenado(arr);
}

void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2){




}

void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2){



}


void calcularTiemposEstimadosLineales(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada){


}


void calcularTiemposEstimadosCuadraticos(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada){


}
