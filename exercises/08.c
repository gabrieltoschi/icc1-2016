#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){

    int a, b, c, aux;
    scanf("%d%d%d", &a, &b, &c);

    // ordem crescente
    if (a <= b){
        aux = a;
        a = b;
        b = aux;
    }

    if (a <= c){
        aux = a;
        a = c;
        c = aux;
    }

    if (b <= c){
        aux = b;
        b = c;
        c = aux;
    }

    if (pow(a, 2) == pow(b, 2) + pow(c, 2)){
        printf("SIM");
    } else {
        printf("NAO");
    }
    return 0;
}
