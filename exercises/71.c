#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	false,
	true
} bool;

typedef struct {
	int id;
	char *name;
	int *rote;
	int roteCt;
} Airport;

typedef struct {
	int *rote;
	int roteCt;
} Itinerary;

typedef struct {	
	Itinerary *answer;
	int airCt;
	Airport **airports;
} Travel;

char *readString(char delim){
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		c = fgetc(stdin);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != delim && c != EOF);

	str[--ct] = '\0';
	return str;
}

int getAirportId(char *token, Airport **airports, int airCt){
	int i, searchedId = -1;
	for (i = 0; i < airCt; i++) {
		if (strcmp(token, airports[i]->name) == 0){
			searchedId = airports[i]->id;
			break;
		}
	}

	return searchedId;
}

int createAirport(Travel *travel, char* newName){
	int newId;

	travel->airports = (Airport **) realloc(travel->airports,
															sizeof(Airport *)*(travel->airCt+1));
	travel->airports[travel->airCt] = (Airport *) malloc(sizeof(Airport));

	travel->airports[travel->airCt]->id = travel->airCt;
	travel->airports[travel->airCt]->name = newName;
	travel->airports[travel->airCt]->rote = NULL;
	travel->airports[travel->airCt]->roteCt = 0;
	newId = travel->airCt;
	travel->airCt++;

	return newId;
}

void createRote(Airport **airports, int from, int to){
	airports[from]->rote = (int *) realloc(airports[from]->rote, 
												sizeof(int)*(airports[from]->roteCt+1));
	airports[from]->rote[airports[from]->roteCt] = to;
	airports[from]->roteCt++;
}	

void readRote(Travel *travel){
	int fromId, toId;

	char *from = readString(' ');
	char *to = readString('\n');

	fromId = getAirportId(from, travel->airports, travel->airCt);
	if (fromId == -1) // aeroporto não cadastrado
		fromId = createAirport(travel, from);
	else free(from);

	toId = getAirportId(to, travel->airports, travel->airCt);
	if (toId == -1) // aeroporto não cadastrado
		toId = createAirport(travel, to);
	else free(to);

	createRote(travel->airports, fromId, toId);
}

void printTravel(Travel *travel){
	int i, j;
	for (i = 0; i < travel->airCt; i++){
		printf(">>>>>>>>> Aeroporto #%d (%s)\n", travel->airports[i]->id, travel->airports[i]->name);
		for (j = 0; j < travel->airports[i]->roteCt; j++){
			printf(">>>>> Rota #%d: vai para %d\n", j, travel->airports[i]->rote[j]);
		}
	}
}

void printAnswer(int *a, int n){
	int i;
	printf(">> ");
	for (i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}

bool isInItinerary(int token, int *rote, int roteCt){
	int i;
	bool ret = false;

	for (i = 0; i < roteCt; i++){
		if (rote[i] == token){
			ret = true;
			break;
		}
	}

	return ret;
}

void bestItinerary(Travel *travel, int dest, int act, Itinerary *itin, int nair){
	int i;

	// CONDIÇÃO DE PARADA: a rota chegou ao seu destino
	// esse é um caminho válido, deve-se verificar se é o melhor
	if (dest == act){
		itin->rote[nair] = act;
		if (nair+1 < travel->answer->roteCt){ // é um caminho melhor que o atual
			memcpy(travel->answer->rote, itin->rote, sizeof(int)*(nair+1));
			travel->answer->roteCt = nair+1;
		}
		return;
	}

	// CONDIÇÃO DE PARADA: a rota entrou em loop
	// esse não é um caminho válido
	if (isInItinerary(act, itin->rote, nair)) return;

	// CONDIÇÃO DE PARADA: a rota chegou ao fim, não existe mais aeroportos para continuar
	// esse não é um caminho válido
	if (travel->airports[act]->roteCt == 0) {
	//	printf("chegamos ao fim, sem saida\n");
		return;
	}

	// PASSO RECURSIVO: siga os demais caminhos possíveis a partir do aeroporto atual
	for (i = 0; i < travel->airports[act]->roteCt; i++){
		itin->rote[nair] = act;
		bestItinerary(travel, dest, travel->airports[act]->rote[i], itin, nair+1);
	}
}

void freeItinerary(Itinerary *it){
	free(it->rote);
	free(it);
}

void freeAirport(Airport *ai){
	free(ai->name);
	free(ai->rote);
	free(ai);
}

void freeTravel(Travel *tr){
	int i;
	freeItinerary(tr->answer);
	for (i = 0; i < tr->airCt; i++){
		freeAirport(tr->airports[i]);
	}
	free(tr->airports);
	free(tr);
}

int main (int argc, char *argv[]){

	Travel *travel;
	Itinerary *itin;
	int n, i, depId, destId;
	char *dep, *dest;

	scanf("%d\n", &n);

	travel = (Travel *) malloc(sizeof(Travel));
	travel->airports = NULL;
	travel->airCt = 0;

	for (i = 0; i < n; i++) readRote(travel);

	dep = readString(' ');
	dest = readString('\n');

	depId = getAirportId(dep, travel->airports, travel->airCt);
	destId = getAirportId(dest, travel->airports, travel->airCt);
	
	itin = (Itinerary *) malloc(sizeof(Itinerary));
	itin->rote = (int *) calloc(travel->airCt, sizeof(int));
	itin->roteCt = 0;
	
	travel->answer = (Itinerary *) malloc(sizeof(Itinerary));
	travel->answer->rote = calloc(travel->airCt, sizeof(int));
	travel->answer->roteCt = travel->airCt + 1;

	bestItinerary(travel, destId, depId, itin, 0);

	for (i = 0; i < travel->answer->roteCt; i++){
		printf("%s ", travel->airports[travel->answer->rote[i]]->name);
	}
	printf("\n");

	free(dep);
	free(dest);
	freeItinerary(itin);
	freeTravel(travel);
	return 0;
}