#include "funciones.hpp"


int main(int argc, char ** argv){

Mat imagen;
Mat output;
vector<vector<Point> > contours;
vector<Point> contorno;
struct parametros params;
int opcion;
int iflag=0, oflag=0;
int n = 10;
string nombreImagen, nombreFichero="contorno.txt";


while((opcion=getopt(argc, argv, "i:o:n:h")) !=-1 ){

    switch(opcion){

      case 'i':
      	//Nombre imagen
      	iflag=1;
      	nombreImagen = optarg;
      	break;

      case 'o':
      	//Nombre fichero salida
      	oflag=1;
      	nombreFichero = optarg;
      	break;

      case 'n':
      	//Para la n
      	n = atoi(optarg);
      	break;

      case '?':
        //Algo ha ido mal
        help();
        exit(-1);
        break;

      default:
        help();
        exit(-1);
        break;
      }
  }

  params.n = n;

  //Seguimos con el main para bingo 

  //Leemos la imagen
  if(iflag){
  	//Hay imagen que leer
  	imagen = imread(nombreImagen, CV_LOAD_IMAGE_ANYDEPTH);
  	if(imagen.empty()){
  		cout << "Imagen especificada invalida" << endl;
  		return -1;
  	}
  	namedWindow("imagen", CV_WINDOW_AUTOSIZE);
    imshow("imagen", imagen);
    waitKey(0);
  }else{
  	//No hay imagen
  	cout << "Especificacion de imagen necesaria" << endl;
  	return -1;
  }

 	Mat contourOutput = imagen.clone();
    findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );

    //Draw the contours
    cv::Mat contourImage(imagen.size(), CV_8UC3, cv::Scalar(0,0,0));

    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contourImage, contours, idx, Scalar(255, 255, 255));
    }

    seleccionaMayorContorno(contours, contorno);

    contornoAFichero(contorno, nombreFichero);

    calculaParametros(params, contorno);

    //Ponemos el rectangulo en la imagen
    rectangle(contourImage, params.boundingBox, Scalar(255,0,0));
    cv::imshow("Contours", contourImage);
    cvMoveWindow("Contours", 200, 0);
    


    muestraParametros(params);

    cv::waitKey(0);


}

