#include <stdio.h>

int main (int argc, char* argv[]){

	int n, a, b;
	int i = 0;
	scanf("%d%d%d", &n, &a, &b);

	do {
		if (i % a == 0 || i % b == 0){
			printf("%d\n", i++);
			n--;
		} else {
			i++;
		}
	} while (n > 0);

	return 0;
}