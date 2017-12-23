#include <stdio.h>

int main (int argc, char *argv[]){

	int n, i;
	scanf("%d", &n);
	int num[n];

	for (i = 0; i < n; i++){
		scanf("%d", &num[i]);
	}

	for (i = n-1; i >= 0; i--){
		printf("%d\n", num[i]);
	}

	return 0;
}