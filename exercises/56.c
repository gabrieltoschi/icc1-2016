#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
	int startMonth;
	double value;
	double rentPerc;
	double rentability;
} title;

title *readTitles(int *lastMonth, int *titlesNumber){
	int currentMonth = 1, ct = 0, i;
	double fraction = 0, fullValue, rentPerc;
	title *invest = NULL;

	while (fraction != -1){
		scanf("%lf", &fraction);

		if (fraction != -1 && fraction != 0){
			scanf("%lf", &fullValue);
			scanf("%lf", &rentPerc);

			invest = (title *) realloc(invest, sizeof(title)*(ct+1));
			invest[ct].startMonth = currentMonth;
			invest[ct].value = fraction * fullValue;
			invest[ct].rentPerc = rentPerc;
			ct++;
		}

		currentMonth++;
	}

	*lastMonth = currentMonth-1;
	*titlesNumber = ct;
	return invest;
}

void rentabilityCalc(title *invest, int lastMonth, int n){
	int i;

	for (i = 0; i < n; i++){
		invest[i].rentability = invest[i].value;
		invest[i].rentability *= pow(1 + invest[i].rentPerc, lastMonth - invest[i].startMonth);
		invest[i].rentability -= invest[i].value;
	}
}

double getTribute(double rent, int months){
	double tax;

	if (months <= 5)
		tax = 0.225;
	if (months >= 6 && months <= 11)
		tax = 0.2;
	if (months >= 12 && months <= 23)
		tax = 0.175;
	if (months >= 24)
		tax = 0.15;

	return rent * tax;
}

void tributeApply(title *invest, int lastMonth, int n){
	int i;

	for (i = 0; i < n; i++)
		invest[i].rentability -= getTribute(invest[i].rentability, lastMonth - invest[i].startMonth);
}

void rentabilityAdd(title *invest, int n){
	int i;

	for (i = 0; i < n; i++)
		invest[i].value += invest[i].rentability;
}

double rentabilitySum(title *invest, int n){
	int i;
	double rent = 0;

	for (i = 0; i < n; i++)
		rent += invest[i].value;

	return rent;
}

int main(int argc, char *argv[])
{
	int lastMonth, ct, i;
	title *invest = readTitles(&lastMonth, &ct);

	rentabilityCalc(invest, lastMonth, ct);
	tributeApply(invest, lastMonth, ct);
	rentabilityAdd(invest, ct);

	printf("%.2lf", rentabilitySum(invest, ct));
	free(invest);
	return 0;
}