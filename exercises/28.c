#include <stdio.h>

int isLower(char l){
	if (97 <= l && l <= 122){
		return 1;
	} else {
		return 0;
	}
}

int isUpper(char l){
	if (65 <= l && l <= 90){
		return 1;
	} else {
		return 0;
	}
}

int main (int argc, char *argv[]){

	int n, i;
	scanf("%d", &n);


	int upper = 0;
	int lower = 0;
	char c;

	for (i = 0; i < n; i++){
		scanf("\n%c", &c);
		upper += isUpper(c);
		lower += isLower(c);
	}

	printf("%d %d\n", upper, lower);
	return 0;
}