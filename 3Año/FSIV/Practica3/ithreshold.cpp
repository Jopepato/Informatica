#include "funciones.hpp"


void main(){



  int opcion;	//Opcion para el getopt
  int tflag=0, mflag=0, rflag=0, cflag=0, iflag=0;  //Flags para el getopt
  int metodo=0;
  int radio=0;
  string nombreImagen;
  float umbral;

  while((opcion=getopt(argc, argv, "tm:r:c:i:")) !=-1 ){

    switch(opcion){

    	case 't':
    		tflag=1;
    	break;

    	case 'm':
    		mflag=1;
    		metodo = atoi(optarg);
    	break;

    	case 'r':
    		rflag=1;
    		radio = atoi(optarg);
    	break;

    	case 'c':
    		cflag=1;
    		umbral = atof(optarg);
    	break;

    	case 'i':
    		iflag=1;
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
}