#include "funciones.hpp"

//Esto es un esqueleto para la practica
using namespace std;

//Los parametros que vamos a necesitar para el programa


int main(int argc, char ** argv){


  int opcion;
  int iflag=0, wflag=0, mflag=0, vflag=0;  //Flags para el getopt
  //Parametros que vamos a recoger
  string nombreImagen;
  string nombreMascara;
  string cadena;
  string delimitador=",";
  string token,token2,token3,token4;
  double x,y,w,h; //Para el roi
  cv::Mat imagen;
  cv::Mat mascara;
  cv::Mat subImagen;
  cv::Mat subMascara;

  while((opcion=getopt(argc, argv, "hiw:m:v:")) !=-1 ){

    switch(opcion){

      case 'h':
          help();
          exit(EXIT_SUCCESS);
        break;

      case 'i':
        if(wflag==0){
          iflag=1;
          cout << "Funcion -i no implementada." << endl;
          exit(-1);
        }else{
          std::cout << "No se puede usar -i y -w a la vez" << std::endl;
        }

        break;

      case 'w':
        if(iflag==0){
          wflag=1;
          //Pillamos los datos que nos han dado
          //Tenemos que substraer la x,y,w,h
          cadena = optarg;
          token = cadena.substr(0, cadena.find(delimitador));
          x = strtod(token.c_str(),NULL);
          
          cadena.erase(0, cadena.find(delimitador) + delimitador.length());
          token = cadena.substr(0, cadena.find(delimitador));
          
          y = strtod(token.c_str(),NULL);

          cadena.erase(0, cadena.find(delimitador) + delimitador.length());
          token = cadena.substr(0, cadena.find(delimitador));
          
          w = strtod(token.c_str(),NULL);
          
          cadena.erase(0, cadena.find(delimitador) + delimitador.length());
          token = cadena.substr(0, cadena.find(delimitador));
          
          h = strtod(token.c_str(),NULL);

        }else{
          std::cout << "No se puede usar -i y -w a la vez" << std::endl;
        }

        break;

      case 'm':
        mflag=1;
        nombreMascara = optarg;

        break;

      case 'v':
        vflag = 1;
        nombreImagen = optarg;
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

   //Una vez hemos recogido los parametros procederemos a cargar las imagenes

   //Primero debemos cargar la imagen que es el parametro obligatorio



     if(vflag==1){
      //Cargamos imagen
      imagen = cv::imread(nombreImagen, -1);
        if(imagen.empty()){
          cout << "No se ha podido cargar la imagen" << endl;
          exit(-1);
        }
      cout << "Imagen cargada con exito" << endl;
      cv::namedWindow("imagen", CV_WINDOW_AUTOSIZE);
      cv::imshow("imagen", imagen);
      cv::waitKey(0);
     }else{
      help();
      exit(-1);
     }

     if(iflag==1){
      //Hacemos lo del roi interactvo

     }


     if(mflag==1){
      //Cargamos la mascara para aplicarla
      mascara = cv::imread(nombreMascara, 0);
        if(mascara.empty()){
          cout << "No se ha podido cargar la mascara" << endl;
          exit(-1);
        }
        cout << "Mascara cargada con exito" << endl;
     }


     if(wflag==1){
      //Hacemos el roi manual
      //Y creamos las subimagenes
      if(x<0 || y<0 || w <0 || h<0 || x>imagen.cols || y>imagen.rows || w+x>imagen.cols || h+y>imagen.rows){

        cout << "Valores para el roi invalidos" << endl;
        exit(-1);
      }else{
        cv::Rect roi1(x,y,w,h);
        subImagen = imagen(roi1);
        cv::namedWindow("roi", CV_WINDOW_AUTOSIZE);
        cv::imshow("roi", subImagen);
        cv::waitKey(0);
          if(mflag==1){
            cv::Rect roi2(x,y,w,h);
            subMascara = mascara(roi2);
          }
      }

     }

     calculaEstadisticosDef(imagen,mascara,subImagen,subMascara,wflag,iflag,mflag);





	return 0;
}