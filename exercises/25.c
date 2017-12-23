#include <stdio.h>

int main (int argc, char *argv[]){

	int i, lines, j;
	int num = 1;

	scanf("%d", &lines);
	
	for (i = 1; i <= lines; i++){
		for (j = 1; j <= i-1; j++){
			printf("%d ", num);
			num += 2;
		}
		printf("%d\n", num);
		num += 2;
	}

	return 0;
}