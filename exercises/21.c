#include <stdio.h>

int main (int argc, char *argv[]){

	double num[4];
	double aux, media;
	scanf("%lf %lf %lf %lf", &num[0], &num[1], &num[2], &num[3]);
	int i, j;
	for (i = 1; i < 4; i++){
		for (j = 0; j < 4-i; j++){
			if (num[j] > num[j+1]){
				aux = num[j];
				num[j] = num[j+1];
				num[j+1] = aux;
			}
		}
	}
	media = (num[1] + num[2] + num[3])/3;
	printf("%.4lf\n", media);
	return 0;
}