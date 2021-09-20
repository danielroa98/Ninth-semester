#include <stdio.h>
#include <string.h>
#include <ctype.h>

char tokens[5][4] = {"ID", "NUM", "PYC", "CMP", "ASG"};
char frase[80] = {"Mary;@123 45=califa;==82fin"};
char lexema[30];
int ind = 0;

void imprimeToken(int num)
{
    printf("Token: %s Lexema: %s\n", tokens[num], lexema);
}
int main(void)
{
    int n = strlen(frase);
    int i, edo = 1;
    while (i < n)
    {
        switch (edo)
        {
        case 1:
            if (isalpha(frase[i]))
            {
                edo = 2;
                lexema[ind++] = frase[i++];
            }
            else
            {
                if (isdigit(frase[i]))
                {
                    edo = 3;
                    lexema[ind++] = frase[i++];
                }
                else
                {
                    if (frase[i] == ';')
                    {
                        lexema[ind++] = frase[i++];
                        //se encontro PYC
                        lexema[ind] = '\0';
                        imprimeToken(2);
                        edo = 1;
                        ind = 0;
                    }
                    else
                    {
                        if (frase[i] == '=')
                        {
                            lexema[ind++] = frase[i++];
                            edo = 4;
                        }
                        else
                        {
                            printf("%c\n", frase[i++]);
                        }
                    }
                }
            }
            break;
        case 2:
            if (isalpha(frase[i]) || isdigit(frase[i]))
            {
                lexema[ind++] = frase[i++];
            }
            else
            {
                //se encontro ID
                lexema[ind] = '\0';
                imprimeToken(0);
                edo = 1;
                ind = 0;
            }
            break;
        case 3:
            if (isdigit(frase[i]))
            {
                lexema[ind++] = frase[i++];
            }
            else
            {
                //se encontro NUM
                lexema[ind] = '\0';
                imprimeToken(1);
                edo = 1;
                ind = 0;
            }
            break;
        case 4:
            if (frase[i] == '=')
            {
                lexema[ind++] = frase[i++];
                //se encontro CMP
                lexema[ind] = '\0';
                imprimeToken(3);
                edo = 1;
                ind = 0;
            }
            else
            {
                //se encontro ASG
                lexema[ind] = '\0';
                imprimeToken(4);
                edo = 1;
                ind = 0;
            }
            break;
        }
    }
    return 0;
}