#include <stdio.h>

int main (int argc, char *argv[]){

	int i, max;
	scanf("%d", &max);

	for (i = 0; i < max; i++){
		printf("%d\n", 1+(i*2));
	}

	return 0;
}