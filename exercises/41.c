#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	int i, read, best = 0, daycount = 1;
	int *days = (int *) calloc(1, sizeof(int));

	for (i = 1; i < 32; i++){
		scanf("%d", &read);
		if (read == best){
			days = (int *) realloc(days, sizeof(int)*(daycount+1));
			days[daycount++] = i; 
		} else if (read > best){
			best = read;
			free(days);
			daycount = 0;
			days = (int *) calloc(1, sizeof(int));
			days[daycount++] = i;
		}
	}

	printf("%d\n", best);
	for (i = 0; i < daycount; i++){
		printf("%d\n", days[i]);
	}

	free(days);
	return 0;
}