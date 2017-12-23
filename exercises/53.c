#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

enum {
	GOLD,   // 0
	SILVER, // 1
	COPPER  // 2
};

typedef struct {
	char *name;
	int *medals;
} country;

typedef struct {
	int start;
	int end;
	int num;
} group;

group* createGroups(group *gp, int *gpcounter, country *ctr, int start, int end, int index){
	int i;
	int n = *gpcounter;
	int lastgroup = -1;
	int byGroup = 0;

	if (gp == NULL) n = 0;

	for (i = start; i < end; i++){
		if (ctr[i].medals[index] != lastgroup){ // new group
			gp = (group *) realloc(gp, sizeof(group)*(n+1));
			gp[n].start = i;
			gp[n].end = i;
			gp[n].num = 1;
			lastgroup = ctr[i].medals[index];
			n++;
		} else { // current group
			gp[n-1].end = i;
			gp[n-1].num += 1;
		}
	}

	*gpcounter = n;
	return gp;
}

void printCountries(country *ctr, int n, int toFree){
	int i;
	for (i = 0; i < n; i++){
		printf("%s %d %d %d\n", ctr[i].name, ctr[i].medals[GOLD],
									ctr[i].medals[SILVER], ctr[i].medals[COPPER]);
		if (toFree){
			free(ctr[i].name);
			free(ctr[i].medals);
		}
	}
}

void sortByCol(country *ctr, int start, int end, int index){
	int i, j;
	country aux;

	for (i = 1; i < end-start; i++){
		for (j = start; j < end-i; j++){
			if (ctr[j].medals[index] < ctr[j+1].medals[index]){
				aux = ctr[j+1];
				ctr[j+1] = ctr[j];
				ctr[j] = aux;
			}
		}
	}
}

int main(int argc, char *argv[]){
	int n, i, goldct,silvct;
	country *ctr;
	group *gold = NULL;
	group *silv = NULL;

	scanf("%d", &n);
	ctr = (country *) malloc(sizeof(country)*n);
	for (i = 0; i < n; i++){
		ctr[i].name = (char *) malloc(sizeof(char)*4);
		ctr[i].medals = (int *) malloc(sizeof(int)*3);
		scanf("%s", ctr[i].name);
		scanf("%d", &ctr[i].medals[GOLD]);
		scanf("%d", &ctr[i].medals[SILVER]);
		scanf("%d", &ctr[i].medals[COPPER]);
	}

	// Sort by Gold
	sortByCol(ctr, 0, n, GOLD);
	
	// Sort by Silver
	gold = createGroups(gold, &goldct, ctr, 0, n, GOLD);

	for (i = 0; i < goldct; i++){
		if (gold[i].num > 1){
			sortByCol(ctr, gold[i].start, gold[i].end+1, SILVER);
		}
	}

	// Sort by Copper
	for (i = 0; i < goldct; i++){
		if (gold[i].num > 1){
			silv = createGroups(silv, &silvct, ctr, gold[i].start, gold[i].end+1, SILVER);
		}
	}

	for (i = 0; i < silvct; i++){
		if (silv[i].num > 1){
			sortByCol(ctr, silv[i].start, silv[i].end+1, COPPER);
		}
	}

	printCountries(ctr, n, true);
	free(ctr);
	free(gold);
	free(silv);

	return 0;
}