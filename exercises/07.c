#include <stdio.h>

int main(int argc, char* argv[]){

    int year;

    scanf("%d", &year);

    if (year % 4 == 0){
        printf("SIM");
    } else {
        printf("NAO");
    }

    return 0;
}
