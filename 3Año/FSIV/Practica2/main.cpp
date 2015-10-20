#include "funciones.hpp"

int main(int argc, char ** argv){

  int opcion;
  int mflag=0,iflag=0;  //Flags para el getopt
  //Parametros que vamos a recoger
  string nombreImagen;
  string nombreMascara;
  vector<Mat> canales;
  int r=0; //Para la r
  cv::Mat imagen;
  cv::Mat imagenHSV;
  cv::Mat imagenMerge;
  cv::Mat mascara;
  cv::Mat subImagen;
  cv::Mat subMascara;
  vector<double> histograma;

  while((opcion=getopt(argc, argv, "i:m:r:h")) !=-1 ){

    switch(opcion){

      case 'h':
          help();
          exit(EXIT_SUCCESS);
        break;

      case 'r':
          //Guardamos el radio
          r = atoi(optarg);

        break;

      case 'm':
        mflag=1;
        nombreMascara = optarg;

        break;

      case 'i':
        iflag = 1;
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

   //Ahora depende de los parametros vamos haciendo distintas cosas

   if(iflag==1){
   	//Cargamos la imagen
   	imagen = imread(nombreImagen, -1);
   		//Comprobamos que no este vacia
   	if(imagen.empty()){
   		cout << "Imagen introducida invalida." << endl;
   		exit(-1);
   	}

   	//Mostramos la imagen
   	cout << "Imagen cargada con exito." << endl;
   	namedWindow("Imagen", CV_WINDOW_AUTOSIZE);
   	imshow("Imagen", imagen);
   	waitKey(0);

   }else{
   	//Nos salimos porque se debe introducir imagen
   	cout << "Imagen obligatoria." << endl;
   	exit(-1);
   }

   //Comprobamos si hay mascara para cargarla

   if(mflag==1){
   	mascara = imread(nombreMascara, 0);
   		if(mascara.empty()){
   			cout << "Mascara no valida" << endl;
   			exit(-1);
   		}else{
   			cout << "Mascara cargada con exito" << endl;
   		}
   }

   
   rellenaVector(histograma);
   

   //Miramos cuantos canales tiene
   if(imagen.channels()==1){
	   	//Monocromatica mas fasi
	   	//Hacemos la ecualizacion y esas cosas

	   	//Miramos si tenemos mascara o no :>
	   	if(mflag==1){
	   		//Tenemos mascara
	   		calcHistogramaMascara(imagen, mascara, histograma, r);
	   		vectorAcumulado(histograma);
	   		normalizaVector(histograma);
	   		
	   		
	   		//ecualizarMascara(imagen, mascara, histograma, r);
	   		ecualizarMascara(imagen,mascara, histograma, r);

	   		cout << "Imagen ecualizada!" << endl;
		   	//Mostramos la imagen ecualizada:
		   	namedWindow("Ecualizacion", CV_WINDOW_AUTOSIZE);
		   	imshow("Ecualizacion", imagen);
		   	waitKey(0);

	   	}else{
	   		//Sin mascara
		   	calcHistograma(imagen, histograma, r);
		   	vectorAcumulado(histograma);
		   	normalizaVector(histograma);
		   	
		   	
		   	ecualizar(imagen, histograma, r);

		   	cout << "Imagen ecualizada!" << endl;
		   	//Mostramos la imagen ecualizada:
		   	namedWindow("Ecualizacion", CV_WINDOW_AUTOSIZE);
		   	imshow("Ecualizacion", imagen);
		   	waitKey(0);
	   	}
   	
   }else{
	   	//HSV, pasamos el V
	   	//Pasamos la imagen de RGB a hsv
	   cvtColor(imagen, imagenHSV, CV_BGR2HSV);

	   //La mostramos (prueba)
	   namedWindow("HSV", CV_WINDOW_AUTOSIZE);
	   imshow("HSV", imagenHSV);
	   waitKey(0);

	   //Spliteamos en canales
	   split(imagenHSV,canales);

	   //Miramos si hay mascara
	   if(mflag==1){

		   	calcHistogramaMascara(canales[2], mascara, histograma, r);
		   	vectorAcumulado(histograma);
		   	normalizaVector(histograma);
		   	
		   	ecualizarMascara(canales[2], mascara, histograma, r);

	   }else{

		   calcHistograma(canales[2],histograma, r);
		   vectorAcumulado(histograma);
		   normalizaVector(histograma);
		   
		   ecualizar(canales[2], histograma, r);

	   }

	   //Hacemos un merge de los canales

	   merge(canales, imagenMerge);

	   //Una vez hecho esto, volvemos a pasar a RGB
	   cvtColor(imagenMerge, imagenMerge, CV_HSV2RGB);

	   //Y la mostramos


		cout << "Imagen ecualizada!" << endl;
		//Mostramos la imagen ecualizada:
		namedWindow("Ecualizacion", CV_WINDOW_AUTOSIZE);
		imshow("Ecualizacion", imagenMerge);
		waitKey(0);

	}

}
