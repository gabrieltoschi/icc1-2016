#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	int questions, students, i, j;
	float correct;
	char test;
	scanf("%d%d\n", &questions, &students);

	char *right = malloc(sizeof(char)*questions);

	for (i = 0; i < questions; i++){
		scanf("%c", &right[i]);
	}
	scanf("%c", &test);

	for (i = 0; i < students; i++){
		correct = 0;
		for (j = 0; j < questions; j++){
			scanf("%c", &test);
			if (test == right[j]) correct++;
		}
		printf("%.2f\n", correct*10/questions);
		scanf("%c", &test);
	}

	free(right);
	return 0;
}