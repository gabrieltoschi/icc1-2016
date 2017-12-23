#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){
	int *dice = (int *) calloc(6, sizeof(int));
	int rd;
	int i;
	int major = 0;

	while (scanf("%d", &rd) != EOF){
		dice[rd-1]++;
	}

	rd = 0;
	for (i = 0; i < 6; i++){
		if (dice[i] == major){
			dice[i] = rd;
		} else if (dice[i] > major){
			major = dice[i];
			dice[i] = --rd;
		}
	}

	for (i = 0; i < 6; i++){
		if (dice[i] == rd) {
			printf("%d\n", i+1);
		}
	}

	printf("%d\n", major);
	free(dice);
	return 0;
}