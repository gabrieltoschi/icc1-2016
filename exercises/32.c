#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	int n, i;
	scanf("%d", &n);

	int *binary = (int *) calloc(32, sizeof(int));

	for (i = 31; i >= 0; i--){
		if (n != 1){
			*(binary+i) = n % 2;
			n /= 2;
		} else {
			*(binary+i) = 1;
			break;
		}
	}

	for (i = 0; i < 32; i++){

		printf("%d", *(binary+i));
	}

	printf("\n");
	free(binary);

	return 0;
}