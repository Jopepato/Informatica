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

void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1){

  double **A, **B, **C;
  double sumax=0, sumay=0;
  double sumaxy=0, sumax2=0;
  double aux;

  //Reservamos memoria dinamica

  A = (double**)malloc(3*sizeof(double*));
  B = (double**)malloc(3*sizeof(double*));
  C = (double**)malloc(3*sizeof(double*));

  for(int i=0; i<3; i++){
    A[i] = (double*)malloc(3*sizeof(double));
    B[i] = (double*)malloc(3*sizeof(double));
    C[i] = (double*)malloc(3*sizeof(double));
  }

  for(int i=0; i<x.size();i++){
    aux = x[i]*log(x[i]);
    sumax += aux;
    sumay += y[i];
    sumaxy = aux*y[i];
    sumax2 = pow(aux,2);
  }

  //Rellenamos las matrices
  //A sera la matriz de la izq
  A[0][0] = x.size();
  A[0][1] = sumax;
  A[1][0] = sumax;
  A[1][1] = sumax2;

  //B es el numerador de a0

  B[0][0] = sumay;
  B[0][1] = sumax;
  B[1][0] = sumaxy;
  B[1][1] = sumax2;

  //C es el numero de a1

  C[0][0] = x.size();
  C[0][1] = sumay;
  C[1][0] = sumax;
  C[1][1] = sumaxy;

  a0 = determinanteDe2(B)/determinanteDe2(A);
  a1 = determinanteDe2(C)/determinanteDe2(A);


}

void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2){

  double **A;
  double **B;
  double **C;
  double **D;
  double sumax = 0;
  double sumax2 = 0;
  double sumax3 = 0;
  double sumax4 = 0;
  double sumaxy = 0;
  double sumax2y = 0;
  double sumay = 0;


  //Reservamos memoria dinamica
  A = (double**)malloc(3*sizeof(double*));
  B = (double**)malloc(3*sizeof(double*));
  C = (double**)malloc(3*sizeof(double*));
  D = (double**)malloc(3*sizeof(double*));
  for(int i=0; i<3; i++){
    A[i] = (double*)malloc(3*sizeof(double));
    B[i] = (double*)malloc(3*sizeof(double));
    C[i] = (double*)malloc(3*sizeof(double));
    D[i] = (double*)malloc(3*sizeof(double));
  }

  //Recorremos el vector para ir rellenando los sumatorios
  for(int i =0; i<x.size(); i++){
    sumax += x[i];
    sumax2 += pow(x[i],2);
    sumax3 += pow(x[i],3);
    sumax4 += pow(x[i],4);
    sumay += y[i];
    sumaxy += x[i]*y[i];
    sumax2y += pow(x[i],2)*y[i];
  }


  //Ahore rellenamos las matrices

  //A sera el denominador comun a todas ellas
  A[0][0] = x.size();
  A[0][1] = sumax;
  A[0][2] = sumay;
  A[1][0] = sumax;
  A[1][1] = sumax2;
  A[1][2] = sumaxy;
  A[2][0] = sumax2;
  A[2][1] = sumax3;
  A[2][2] = sumax4;


  //B sera el numerador de a0

  B[0][0] = sumay;
  B[0][1] = sumax;
  B[0][2] = sumax2;
  B[1][0] = sumaxy;
  B[1][1] = sumax2;
  B[1][2] = sumax3;
  B[2][0] = sumax2y;
  B[2][1] = sumax3;
  B[2][2] = sumax4;

  //C sera el numerador de a1

  C[0][0] = x.size();
  C[0][1] = sumay;
  C[0][2] = sumax2;
  C[1][0] = sumax;
  C[1][1] = sumaxy;
  C[1][2] = sumax3;
  C[2][0] = sumax2;
  C[2][1] = sumax2y;
  C[2][2] = sumax4;

  //D sera el numerador de a2
  D[0][0] = x.size();
  D[0][1] = sumax;
  D[0][2] = sumay;
  D[1][0] = sumax;
  D[1][1] = sumax2;
  D[1][2] = sumaxy;
  D[2][0] = sumax2;
  D[2][1] = sumax3;
  D[2][2] = sumax2y;


  //Ahora calculamos a0, a1 y a2 con los determinantes

  a0 = determinanteDe3(B)/determinanteDe3(A);
  a1 = determinanteDe3(C)/determinanteDe3(A);
  a2 = determinanteDe3(D)/determinanteDe3(A);

}


void calcularTiemposEstimadosLineales(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada, double &r2){


}


void calcularTiemposEstimadosCuadraticos(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada, double &r2){


}


double determinanteDe2(double * matriz[]){

  double resultado;

  resultado = (matriz[0][0] * matriz[1][1])-(matriz[0][1] * matriz[1][0]);

  return resultado;

}

double determinanteDe3(double * matriz[]){

  double resultado;


  resultado = matriz[0][0]*matriz[1][1]*matriz[2][2] +
              matriz[0][1]*matriz[1][2]*matriz[2][0] +
              matriz[1][0]*matriz[2][1]*matriz[0][2];


  resultado = resultado - (matriz[2][0]*matriz[1][1]*matriz[0][2] +
                           matriz[0][0]*matriz[1][2]*matriz[2][1] +
                           matriz[1][0]*matriz[0][1]*matriz[2][2]);

  return resultado;
}