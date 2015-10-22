#include "funciones.hpp"

int main(int argc, char ** argv){

  int opcion;
  int mflag=0,iflag=0, rflag=0;  //Flags para el getopt
  //Parametros que vamos a recoger
  string nombreImagen;
  string nombreMascara;
  string nombreOutput = "output.png";
  vector<Mat> canales;
  int r=0; //Para la r
  cv::Mat imagen;
  cv::Mat imagenHSV;
  cv::Mat imagenMerge;
  cv::Mat mascara;
  cv::Mat subImagen;
  cv::Mat subMascara;
  vector<double> histograma;

  while((opcion=getopt(argc, argv, "i:m:r:ho:")) !=-1 ){

    switch(opcion){

      case 'h':
          help();
          exit(EXIT_SUCCESS);
        break;

      case 'r':
          //Guardamos el radio
      	  rflag=1;
          r = atoi(optarg);
          if(r<0){
          	cout << "Parametro 'r' introducido no valido" << endl;
          	exit(-1);
          }

        break;

      case 'm':
        mflag=1;
        nombreMascara = optarg;

        break;

      case 'i':
        iflag = 1;
        nombreImagen = optarg;
        break;
      
      case 'o':
      	nombreOutput = optarg;
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

   	//Tenemos que comprobar que la r no sea mayor que la mitad del ancho y alto
   	if(rflag==1){
   		if(r>imagen.rows/2 || r>imagen.cols/2){
   			cout << "Parametro 'r' introducido no valido" << endl;
   			exit(-1);
   		}
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

    //Miramos si tenemos radio o no

      if(r==0){
          	   	//Miramos si tenemos mascara o no :>
          	   	if(mflag==1){
          	   		//Tenemos mascara
          	   		calcHistogramaMascara(imagen, mascara, histograma);
          	   		vectorAcumulado(histograma);
          	   		normalizaVector(histograma);   		
          	   		//ecualizarMascara(imagen, mascara, histograma, r);
          	   		ecualizarMascara(imagen,mascara, histograma);

          	   		

          	   	}else{
          	   		//Sin mascara
          		   	calcHistograma(imagen, histograma);
          		   	vectorAcumulado(histograma);
          		   	normalizaVector(histograma);		   	
          		   	ecualizar(imagen, histograma);
          	   	}
      }else{

        cout << "Ecualizando..." << endl;
        
        for(int x=r; x<imagen.rows-r; x++){
          for(int y=r; y<imagen.cols-r; y++){

            Mat ventana(imagen,Rect(x-r,y-r,2*r+1,2*r+1));

            if(mflag==1){
              Mat ventMask(mascara,Rect(x-r,y-r,2*r+1,2*r+1));

              calcHistogramaMascara(ventana, ventMask, histograma);
              vectorAcumulado(histograma);
              normalizaVector(histograma);

              ecualizarMascaraRadio(imagen,mascara, histograma, x,y);

            }else{

              calcHistograma(ventana, histograma);
              vectorAcumulado(histograma);
              normalizaVector(histograma);
              ecualizarRadio(imagen, histograma, x,y);

            }
          }
        }
      }

	   	cout << "Imagen ecualizada!" << endl;
		   	//Mostramos la imagen ecualizada:
		   	namedWindow("Ecualizacion", CV_WINDOW_AUTOSIZE);
		   	imshow("Ecualizacion", imagen);
		   	waitKey(0);
		   	imwrite(nombreOutput, imagen);

		   	cout << "Imagen pasada a fichero con exito!" << endl;



        //Terminado si es monocromatica




	
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
    if(r==0){
      	   //Miramos si hay mascara
      	   if(mflag==1){

      		   	calcHistogramaMascara(canales[2], mascara, histograma);
      		   	vectorAcumulado(histograma);
      		   	normalizaVector(histograma);
      		   	
      		   	ecualizarMascara(canales[2], mascara, histograma);

      	   }else{

      		   calcHistograma(canales[2],histograma);
      		   vectorAcumulado(histograma);
      		   normalizaVector(histograma);
      		   
      		   ecualizar(canales[2], histograma);

      	   }
       }else{

        cout << "Ecualizando..." << endl;

        for(int x=r; x<canales[2].rows-r; x++){
          for(int y=r; y<canales[2].cols-r; y++){

            Mat ventana(canales[2],Rect(y-r,x-r,2*r+1,2*r+1));

            if(mflag==1){
              Mat ventMask(mascara,Rect(y-r,x-r,2*r+1,2*r+1));

              calcHistogramaMascara(ventana, ventMask, histograma);
              vectorAcumulado(histograma);
              normalizaVector(histograma);
              ecualizarMascaraRadio(canales[2],mascara, histograma, x,y);

            }else{

              calcHistograma(ventana, histograma);
              vectorAcumulado(histograma);
              normalizaVector(histograma);
              ecualizarRadio(canales[2], histograma, x,y);
            }

          }
        }

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
		destroyWindow("Ecualizacion");
		//Ahora guardamos la imagen
		imwrite(nombreOutput, imagenMerge);

		cout << "Imagen pasada a fichero con exito" << endl;
	}

}
