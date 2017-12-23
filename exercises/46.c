#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){
	int n, i, j;
	long long int ant, aux;
	long long int *l;
	scanf("%d", &n);

	l = (long long int *) calloc(n+1, sizeof(long long int));

	for (i = 0; i < n; i++){
		for (j = 0; j <= (i/2); j++){
			if (j == 0) {
				l[j] = 1;
				ant = 1;
				printf("%lli", l[j]);
			} else {
				aux = l[j];
				l[j] += ant;
				ant = aux;
				printf("%lli", l[j]);
			}
		}

		aux = (i+1) % 2 == 0 ? (i/2) : (i/2)-1;
		for (j = (i/2)+1; j <= i; j++){
			l[j] = l[aux--];
			printf("%lli", l[j]);
		}
		printf("\n");
	}

	free(l);
}