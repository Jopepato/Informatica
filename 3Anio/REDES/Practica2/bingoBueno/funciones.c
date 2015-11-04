#include "funciones.h"

int compruebaElementoVector(int * vector, int elem, int nelem){
int i=0;
	for(i=0; i<nelem; i++){
		if(vector[i]==elem){
			return 1;
		}
	}

	return 0;

}

int compruebaElementoMatriz(int ** matriz, int elem){
	//Con esta funcion comprobamos si el elemento esta en la matriz
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(matriz[i][j] == elem){
				return 1;
			}
		}
	}
	
return 0;

}

int ** generaCarton(){
	int ** carton;
	int i,j,k=0;
	int aux;
	int quita;
	int quitados[4];
	int siguiente;
	//reservamos memoria
	
	carton = (int **)malloc(3*sizeof(int*));
	for(i=0; i<3; i++){
		carton[i] = (int*)malloc(9*sizeof(int));
	}

	//Rellenamos el carton con ceros
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			carton[i][j]=0;
		}
	}
	
	//Hacemos las bolas aleatorias para el carton

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			//Hacemos un if por cada columna para pasarle el numero que le corresponde
			aux = (rand()%10) +j*10;
			if(j==8){
				aux = (rand()%11) +j*10;
			}
			if(aux==0){
				aux=1;
			}
			if(!compruebaElementoMatriz(carton, aux)){
				carton[i][j] = aux;
			}else{
				j--;
			}
		}
	}
	//Rellenamos el vector de quitados con 10
	for(i=0; i<4; i++){
		quitados[i] = 10;
	}

	//Ahora deberemos quitar 4 numeros por fila
	for(i=0; i<3;i++){
		siguiente=1;
		while(k!=4){
			quita = rand()%9;
			if(!compruebaElementoVector(quitados, quita, 4)){
				quitados[k] = quita;
				k++;
				carton[i][quita] = 0;
			}
		}
		for(j=0; j<4; j++){
		quitados[i] = 10;
		}
		k=0;
	}
	
	return carton;
}


void muestraCarton(int ** carton){
	int i,j;

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(carton[i][j]==0){
				printf("X\t");
			}else{
			printf("%d\t", carton[i][j]);
			}
		}
		printf("\n");
	}

}