#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[]){

	int num = 0;
	int let = 0;
	char c;

	do {
		scanf("%c", &c);
		if (isalpha(c)){  // alfabetico
			let++;
		}

		if (isdigit(c)){  // numerico
			num++;
		}
	} while (c != 10);

	printf("%d\n%d\n", let, num);

	return 0;
}