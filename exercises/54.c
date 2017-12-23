#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int isOperation(char c){
	if (c == 42 || c == 43 || c == 45 || c == 47) return 1;
		else return 0;
}

int isEnd(FILE *stream, char end){
	char c;
	c = fgetc(stream);

	if (c == end){
		return 1;
	} else {
		ungetc(c, stream);
		return 0;
	}
}

char *readOp(FILE *stream, char end, int *endOfFile){
	char *op = NULL;
	char c;
	int i = 0;

	do {
		c = fgetc(stream);
		op = (char *) realloc(op, sizeof(char)*(i+1));
		op[i++] = c;
	} while (c != ' ' && c != EOF && c != '\n');

	if (c == end) *endOfFile = 1;
	op[--i] = '\0';
	return op;
}

double *stackPush(double *stack, double new, int *top){
	stack = realloc(stack, sizeof(double)*((*top)+1));
	stack[*top] = new;
	*top += 1;
	return stack;
}

double *stackPop(double *stack, int *top){
	stack = realloc(stack, sizeof(double)*((*top)-1));
	*top -= 1;
	return stack;
}

double *doOperation(double *stack, int *top, char op){
	switch (op){
		case '+':
			stack[(*top)-2] += stack[(*top)-1];
			break;
		case '-':
			stack[(*top)-2] -= stack[(*top)-1];
			break;
		case '*':
			stack[(*top)-2] *= stack[(*top)-1];
			break;
		case '/':
			stack[(*top)-2] /= stack[(*top)-1];
			break;
	}

	stack = stackPop(stack, top);
	return stack;
}

void printStack(double *stack, int n){
	int i;
	for (i = n-1; i >= 0; i--){
		printf("[%lf]\n", stack[i]);
	}
}

int main(int argc, char *argv[]){
	
	double *stack;
	int top = 0;
	char *op;
	int endOfFile = 0;

	stack = (double *) malloc(sizeof(double));

	while(!endOfFile){
		op = readOp(stdin, '\n', &endOfFile);
		if (isOperation(*op)) { // é uma operação
			stack = doOperation(stack, &top, *op);
		} else { // é um número
			stack = stackPush(stack, atof(op), &top);
		}
		free(op);
	}

	printf("%lf\n", *stack);
	free(stack);

	return 0;
}