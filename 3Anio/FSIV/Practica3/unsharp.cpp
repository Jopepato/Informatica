#include "funciones.hpp"


int main(int argc, char **argv){

  int opcion;	//Opcion para el getopt
  int vflag=0, rflag=0, nflag=0, glfag=0, iflag=0, mflag=0, oflag=0;  //Flags para el getopt
  float r=0.5, g=1.0;
  int n=2;
  string nombreImagen;
  string nombreMascara;
  string nombreSalida = "output.png";
  Mat imagen;
  Mat mascara;
  vector<Mat> canales;

  while((opcion=getopt(argc, argv, "vr:n:g:i:o:m:")) !=-1 ){

    switch(opcion){

      case 'v':
        vflag=1;
      break;

      case 'r':
        rflag=1;
        r=atof(optarg);
        if(r<0 || r>1){
          cout << "Valor de 'r' introducido invalido" << endl;
          exit(-1);
        }
      break;

      case 'n':
        nflag=1;
        n = atoi(optarg);
        if(n<0 || n>10){
          cout << "Valor de 'n' introducido invalido" << endl;
          exit(-1);
        }
      break;

      case 'g':
        glfag=1;
        g = atof(optarg);
        if(g<0.0 || g>5.0){
          cout << "Valor de 'g' introducido invalido" << endl;
          exit(-1);
        }
      break;

      case 'i':
        iflag=1;
        nombreImagen = optarg;
      break;

      case 'm':
        mflag=1;
        nombreMascara=optarg;
      break;

      case 'o':
        oflag=1;
        nombreSalida=optarg;
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

   //Primero cargaremos la imagen

   if(iflag==1){
    imagen = imread(nombreImagen, CV_LOAD_IMAGE_ANYDEPTH);
    if(imagen.empty()){
      cout << "Imagen especificada invalida" << endl;
      exit(-1);
    }else{
      cout << "Imagen cargada con exito" << endl;
      if(vflag==1){
        namedWindow("Imagen", CV_WINDOW_AUTOSIZE);
        imshow("Imagen", imagen);
        waitKey(0);
        destroyWindow("Imagen");
      }
    }
    }else{
     cout << "La imagen es necesaria" << endl;
     exit(-1);
   }


   //Miramos si tiene mascara para cargarla
   if(mflag==1){
    //Cargamos la mascara
    mascara = imread(nombreMascara, 0);
    if(mascara.empty()){
      cout << "Mascara especificada invalida" << endl;
      exit(-1);
    }
   }


   //Ahora miramos los canales para hacer cosas distintas dependiendo

   if(imagen.channels()==1){
    //Imagen monocromatica
    Mat imagenPasoBaja = imagen;
    Mat output;
    Mat fourier;

    if(mflag==1){
      //Con mascara
    }else{
      //Sin mascara

      cout << "Hola1" << endl;
      dft(imagen, fourier);
      //Aplicamos el filtro butterworth
      cout << "Hola2" << endl;
      namedWindow("Transformada", CV_WINDOW_AUTOSIZE);
      imshow("Transformada", fourier);
      waitKey(0);


      //Y hacemos la inversa de fourier
      dft(fourier, imagenPasoBaja, DFT_INVERSE);


      //Hacemos unsharp
      output = (g+1)*imagen - g*imagenPasoBaja;

      //Ahora la mostramos
      namedWindow("Terminao", CV_WINDOW_AUTOSIZE);
      imshow("Terminao", output);
      waitKey(0);
    }


   }else{
    //Imagen a color, pasamos a HSV
    cvtColor(imagen, imagen, CV_BGR2HSV);
    //Spliteamos la imagen en canales
    split(imagen, canales);

    Mat fourier;

    dft(canales[2], fourier, DFT_REAL_OUTPUT);

    namedWindow("Transformada", CV_WINDOW_AUTOSIZE);
    imshow("Transformada", fourier);
    waitKey(0);
    if(mflag==1){
      //Con mascara
    }else{
      //Sin mascara
    }

   }



return 0;

}