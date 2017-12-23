#include <stdio.h>

int main(int argc, char* argv[]){

    int n, i, j, aux;
    scanf("%d", &n);
    int num[n];
    for (i = 0; i < n; i++){
        scanf("%d", &num[i]);
    }

    i = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (num[i] > num[j]){
                aux = num[i];
                num[i] = num[j];
                num[j] = aux;
            }
        }
    }

    printf("max: %d\n", num[0]);
    printf("min: %d\n", num[n-1]);
    return 0;
}
