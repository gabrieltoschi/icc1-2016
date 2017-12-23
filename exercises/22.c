#include <stdio.h>

int main (int argc, char *argv[]){

	int a1, r, n;
	long long int an, sn;
	scanf("%d%d%d", &a1, &r, &n);

	an = a1 + ((n-1)*r);
	sn = ((a1 + an)*n)/2;
	printf("%lli\n%lli\n", an, sn);

	return 0;
}