#include "estimaciones.hpp"


void calcularAjusteIterativo(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3){

	//Calcularemos a0 a1 a2 y a3 con la regla de cramer

  //Primero debemos rellenar las matrices
  Matriz<double> A(4,4);//Almacenará el denominador comun
  Matriz<double> B(4,4);//Numerador de a0
  Matriz<double> C(4,4);//Numerador de a1
  Matriz<double> D(4,4);//Numerador de a2
  Matriz<double> E(4,4);//Numerador de a3

  //Las rellenamos
  A.elemento(1,1, x.size());
  A.elemento(1,2, sumatorioVector(x));
  A.elemento(1,3, sumatorio2Vector(x));
  A.elemento(1,4, sumatorio3Vector(x));
  A.elemento(2,1, sumatorioVector(x));
  A.elemento(2,2, sumatorio2Vector(x));
  A.elemento(2,3, sumatorio3Vector(x));
  A.elemento(2,4, sumatorio4Vector(x));
  A.elemento(3,1, sumatorio2Vector(x));
  A.elemento(3,2, sumatorio3Vector(x));
  A.elemento(3,3, sumatorio4Vector(x));
  A.elemento(3,4, sumatorio5Vector(x));
  A.elemento(4,1, sumatorio3Vector(x));
  A.elemento(4,2, sumatorio4Vector(x));
  A.elemento(4,3, sumatorio5Vector(x));
  A.elemento(4,4, sumatorio6Vector(x));

  //Para las demas matrices solo tendremos que cambiar una columna
  B =A;
  //Cambiamos la columna 1
  B.elemento(1,1, sumatorioVector(y));
  B.elemento(2,1, sumatorioxyVector(x,y));
  B.elemento(3,1, sumatoriox2yVector(x,y));
  B.elemento(4,1, sumatoriox3yVector(x,y));

  C=A;
  //Cambiamos la columna 2
  C.elemento(1,2, sumatorioVector(y));
  C.elemento(2,2, sumatorioxyVector(x,y));
  C.elemento(3,2, sumatoriox2yVector(x,y));
  C.elemento(4,2, sumatoriox3yVector(x,y));

  D=A;
  //Cambiamos la columna 3
  D.elemento(1,3, sumatorioVector(y));
  D.elemento(2,3, sumatorioxyVector(x,y));
  D.elemento(3,3, sumatoriox2yVector(x,y));
  D.elemento(4,3, sumatoriox3yVector(x,y));

  E=A;
  //Cambiamos la columna 4
  E.elemento(1,4, sumatorioVector(y));
  E.elemento(2,4, sumatorioxyVector(x,y));
  E.elemento(3,4, sumatoriox2yVector(x,y));
  E.elemento(4,4, sumatoriox3yVector(x,y));


  //Y ahora calculamos a0 a1 a2 y a3
  a0 = determRecursivo(B, 4)/determRecursivo(A, 4);
  a1 = determRecursivo(C, 4)/determRecursivo(A, 4);
  a2 = determRecursivo(D, 4)/determRecursivo(A, 4);
  a3 = determRecursivo(E, 4)/determRecursivo(A, 4);


	
}

void calcularAjusteRecursivo(const vector<double> &x, const vector<double> &y, double &a0, double &a1){

  //El ajuste recursivo es como el lineal pero le pasamos el vector de factoriales
  //Declaramos 3 matrices 2x2
  Matriz<double> A(2,2); //Denominador comun
  Matriz<double> B(2,2); //Numerador para a0
  Matriz<double> C(2,2); //Numerador para a1

  A.elemento(1,1, x.size());
  A.elemento(1,2, sumatorioVector(x));
  A.elemento(2,1, sumatorioVector(x));
  A.elemento(2,2, sumatorio2Vector(x));

  //Para la matriz B deberemos cambiar la columna 1
  B=A;
  B.elemento(1,1, sumatorioVector(y));
  B.elemento(2,1, sumatorioxyVector(x,y));

  //Para la matriz C deberemos cambiar la columna 2
  C=A;
  C.elemento(1,2, sumatorioVector(y));
  C.elemento(2,2, sumatorioxyVector(x,y));

  a0 = determRecursivo(B, 2)/determRecursivo(A, 2);
  a1 = determRecursivo(C, 2)/determRecursivo(A, 2);


}


void calcularTiemposEstimadosIterativo(const vector<double> &x, const vector<double> &y, vector<double> &yEst, double &a0, double &a1, double &a2, double &a3, double &r2){

  //El tiempo estimado iterativo es polinomico, lo iremos guardando en yEstimada
  //Ademas calcularemos r2
  double aux=0.0;
  for(unsigned int i=0; i<x.size(); i++){
    aux = a0 + a1*x[i] + a2*pow(x[i],2) + a3*pow(x[i],3);
    yEst.push_back(aux);
  }

  //Ahora calculamos las medias y varianzas para calcular r2
  r2 = varianzaVector(yEst, mediaVector(yEst))/varianzaVector(y, mediaVector(y));


}

void calcularTiemposEstimadosRecursivo(const vector<double> &x, const vector<double> &y, vector<double> &yEst, double &a0, double &a1, double &r2){

  //Nos pasan el vector con los factoriales
  double aux=0.0;
  for(unsigned int i=0; i<x.size(); i++){
    aux = a0 + a1*x[i];
    yEst.push_back(aux);
  }

  //Calculamos r2
  r2 = varianzaVector(yEst, mediaVector(yEst))/varianzaVector(y, mediaVector(y));

}


//Funcion para guardar los tiempos en un fichero
void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE,
          const vector<double> &tS, const vector<double> &tSE, string fichero){

  ofstream file;

  file.open(fichero.c_str());

  //Recorremos el vector n y vamos metiendo los datos

  for(unsigned int i=0; i<n.size(); i++){
    file << n[i] << " " << tNS[i] << " " << tNSE[i] << " " << tS[i] << " " << tSE[i] << "\n";
  }



  file.close();

}