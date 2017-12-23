#include <stdio.h>

int main(int argc, char* argv[]){

    float a, b;
    char op;

    scanf("%f", &a);
    scanf(" %c", &op);
    scanf("%f", &b);

    switch (op){
        case '+':
            printf("%f", a + b);
            break;
        case '-':
            printf("%f", a - b);
            break;
        case '*':
            printf("%f", a * b);
            break;
        case '/':
            printf("%f", a / b);
            break;
        case '%':
            printf("%f", (100*a)/b);
            break;
    }

    return 0;
}
