//Funcion del generar carton

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int ** generaCarton(){

	int ** carton;
	int i,j;
	//reservamos memoria
	
	carton = (int **)malloc(3*sizeof(int*));
	for(i=0; i<3; i++){
		carton[i] = (int*)malloc(9*sizeof(int));
	}
	
	//Hacemos las bolas aleatorias para el carton

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			carton[i][j] = rand()%100;
		}
	}
	
	return carton;

}

int compruebaElemento(int ** matriz, int elem){
	//Con esta funcion comprobamos si el elemento esta en la matriz
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			if(matriz[3][9] == elem){
				return 1;
			}
		}
	}
	
return 0;

}

void muestraMatriz(int **carton){

	int i,j;

	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			printf("%d\t", carton[i][j]);
		}
		printf("\n");
	}
}





void main(){
	
	srand(time(NULL));
	int **carton;

	carton = generaCarton();

	muestraMatriz(carton);
	


	

}
