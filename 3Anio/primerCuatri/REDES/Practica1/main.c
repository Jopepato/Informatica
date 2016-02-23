#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	int vector[10] = { [0 ... (10-1)] = 10};

	for(i=0; i<10; i++){
		printf("%d", vector[i]);
	}
}