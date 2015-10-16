#include "estimaciones.hpp"


double calcularAjusteIterativo(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3){

	




	
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