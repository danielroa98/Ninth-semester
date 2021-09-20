#include<stdio.h>
#include<string.h>
#include<ctype.h>

char tokens[5][4]={"ID","NUM","PYC","CMP","ASG"};
char frase[80]={"Mary;@123 45=califa;==82fin"};
char lexema[30];
int ind=0;

void imprimeToken(int num){
    printf("Token: %s Lexema: %s\n",tokens[num],lexema);
}

int main(void){
    printf("Hola!");
    return 0;
}
