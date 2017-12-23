#include <stdio.h>

int main (int argc, char *argv[]){

	int dividendo, divisor;
	int quociente = 0;
	scanf("%d%d", &dividendo, &divisor);

	if (dividendo == 0){
		printf("%d\n%d\n", 0, 0);
		return 0;
	}

	do {
		dividendo -= divisor;
		quociente++;
	} while (!(dividendo < divisor));

	printf("%d\n%d\n", quociente, dividendo);
	return 0;
}