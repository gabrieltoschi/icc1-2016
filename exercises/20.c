#include <stdio.h>

int main (int argc, char *argv[]){

	int n, j, m, ct, mod, i;
	scanf("%d%d%d", &n, &j, &m);
	ct = 0;
	mod = j % m;

	for (i = 1; ct < n; i++){
		if (i % m == mod){
			printf("%d\n", i);
			ct++;
		}
	}

	return 0;
}