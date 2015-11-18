#include "funciones.hpp"


int main(int argc, char **argv){

  int opcion;	//Opcion para el getopt
  int vflag=0, rflag=0, nflag=0, glfag=0, iflag=0, mflag=0, oflag=0;  //Flags para el getopt
  float r=0.5, g=1.0;
  int n=2;
  string nombreImagen;
  string nombreMascara;
  string nombreSalida = "output.png";
  Mat imagen, padded, complexImg, filter, filterAux, imagenSalida, filterSalida, imagenFrecuencias, imagenFrecuenciasSinOrden, imagenHSV;
  Mat complexAux;
  Mat salida;
  Mat imagenPasoBaja;
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

   //Calculamos r
   r=(r)*(sqrt(pow((imagen.rows),2.0)+pow((imagen.cols),2.0))/2);

   int M = getOptimalDFTSize(imagen.rows);
   int N = getOptimalDFTSize(imagen.cols);


   //Miramos si tiene mascara para cargarla
  if(mflag==1){
    //Cargamos la mascara
    mascara = imread(nombreMascara, 0);
    if(mascara.empty()){
      cout << "Mascara especificada invalida" << endl;
      exit(-1);
    }else{
	cout << "Mascara cargada con exito" << endl;
	   }
  }


   //Ahora miramos los canales para hacer cosas distintas dependiendo

   if(imagen.channels()==1){
    //Imagen monocromatica

    imagen.convertTo(imagenPasoBaja,CV_32F, 1.0/255.0);
    copyMakeBorder(imagenPasoBaja, padded, 0, M-imagenPasoBaja.rows, 0, N - imagenPasoBaja.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    merge(planes, 2, complexImg);

    dft(complexImg, complexImg);
    filter = complexImg.clone();
    filterAux = complexImg.clone();
    complexAux = complexImg.clone();
    shiftDFT(complexImg);
    shiftDFT(complexAux);

    butterworth(filter, r, n);
    butterworth(filterAux, r, 0);
    mulSpectrums(complexImg, filter, complexImg, 0);
    mulSpectrums(complexAux, filterAux, complexAux, 0);
    shiftDFT(complexImg);
    shiftDFT(complexAux);

    //Falta hacer lo de poder mostrarla
    imagenFrecuencias = create_spectrum(complexImg);
    imagenFrecuenciasSinOrden = create_spectrum(complexAux);

    //Hacemos la inversa
    idft(complexImg, complexImg, DFT_SCALE);
    split(complexImg, planes);
    normalize(planes[0], imagenSalida, 0, 1, CV_MINMAX);
    split(filter, planes);
    normalize(planes[0], filterSalida, 0, 1, CV_MINMAX);

   salida = imagenPasoBaja.clone();
   /* imshow("Salida", salida);
    imshow("ImagenSalida", imagenSalida);
    waitKey(0);
*/
    if(mflag==1){
      //Con mascara procesaremos pixel por pixel
      //Recorremos la imagen
      for(int i=0; i<imagen.rows; i++){
        for(int j=0; j<imagen.cols;j++){
          if(mascara.at<uchar>(i,j)!=0){
            salida.at<float>(i,j) = (g+1)*(imagenPasoBaja.at<float>(i,j)) - (g*imagenSalida.at<float>(i,j));
          }
        }
      }
    }else{
      //Sin mascara lo haremos de forma inmediata
      for(int i=0; i<imagen.rows; i++){
        for(int j=0; j<imagen.cols;j++){
            salida.at<float>(i,j) = ((g+1)*imagenPasoBaja.at<float>(i,j)) - (g*imagenSalida.at<float>(i,j));
        }
      }
    }

    salida.convertTo(salida, CV_8U, 255.0, 0.0);

    if(vflag==1){
      imshow("Imagen final", salida);
      imshow("Filtro Butterworth", filterSalida);
      imshow("Espectro", imagenFrecuencias);
      imshow("Espectro de imagen sin orden", imagenFrecuenciasSinOrden);
      waitKey(0);
    }

   }else{
    //Spliteamos la imagen en canales
    cvtColor(imagen, imagenHSV, CV_BGR2HSV);
    split(imagenHSV, canales);
    Mat temporal;
    canales[2].convertTo(imagenPasoBaja, CV_32F, 1.0/255.0);
    copyMakeBorder(imagenPasoBaja, padded, 0, M-imagenPasoBaja.rows, 0, N - imagenPasoBaja.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    merge(planes, 2, complexImg);

    dft(complexImg, complexImg);

    filter = complexImg.clone();

    shiftDFT(complexImg);

    butterworth(filter, r, n);
    mulSpectrums(complexImg, filter, complexImg, 0);
    shiftDFT(complexImg);

    //Falta hacer lo de poder mostrarla
    imagenFrecuencias = create_spectrum(complexImg);

    //Hacemos la inversa
    idft(complexImg, complexImg, DFT_SCALE);
    split(complexImg, planes);
    normalize(planes[0], imagenSalida, 0, 1, CV_MINMAX);
    split(filter, planes);
    normalize(planes[0], filterSalida, 0, 1, CV_MINMAX);

    Mat salida = imagen.clone();
    canales[2] = imagenPasoBaja.clone();
    if(mflag==1){
      //Con mascara
      for(int i=0; i<canales[2].rows; i++){
        for(int j=0; j<canales[2].cols;j++){
          if(mascara.at<uchar>(i,j)!=0){
            canales[2].at<float>(i,j) = ((g+1)*imagenPasoBaja.at<float>(i,j)) - (g*imagenSalida.at<float>(i,j));
          }
        }
      }
    }else{
      //Sin mascara
      for(int i=0; i<canales[2].rows; i++){
        for(int j=0; j<canales[2].cols;j++){
            canales[2].at<float>(i,j) = ((g+1)*imagenPasoBaja.at<float>(i,j)) - (g*imagenSalida.at<float>(i,j));
        }
      }
    }

    canales[2].convertTo(canales[2], CV_8U, 255.0, 0.0);
    merge(canales, salida);
    cvtColor(salida, salida, CV_HSV2BGR);

    salida.convertTo(salida, CV_8U, 255.0, 0.0);

    if(vflag==1){
      imshow("Imagen final", salida);
      imshow("Filtro Butterworth", filterSalida);
      imshow("Espectro", imagenFrecuencias);
      imshow("Espectro de imagen sin orden", imagenFrecuenciasSinOrden);
      waitKey(0);
    }


   }
   //Y escribimos la imagen a fichero
   imwrite(nombreSalida, salida);

return 0;

}