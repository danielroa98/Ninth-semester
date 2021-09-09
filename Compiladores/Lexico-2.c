#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//char tokens[5][4]={"ID","NUM","PYC","CMP","ASG"};

/*
OPREL    <, <=, >, >=, == -> Sergio
ASIG        = --> Roa
OPAR      +, -, *, /, %, **, ++, -- -> Sebas
ID             letra(letra|digito)+ ----> Done
ENT          digito+
REAL        digito+   ( .digito+(E(+|-)?digito+) | .digito+ | E(+|-)?digito+ )
ERR         cualquier cosa que no empate con ningún token (agrupado en el mismo lexema si son varios símbolos concatenados) p.e. @#$+  debe quedar ERR @#$   OPAR +

*/
char tokens[8][5] = {"OPREL", "ASIG", "PYC", "OPAR", "ID", "ENT", "REAL", "ERR"};
char lexema[30];

char operaciones[6] = {'+', '-', '*', '/', '%'};
char comparaciones[4] = {'<', '>'};

int ind = 0;
int nline = 0;

bool isOPAR(char x)
{
    for (int i = 0; i < 4; i++)
    {
        if (x == operaciones[i])
        {
            return true;
        }
    }

    return false;
}

bool isOPREL(char x)
{
    for (int i = 0; i < 3; i++)
    {
        if (x == comparaciones[i])
        {
            return true;
        }
    }

    return false;
}

void imprimeToken(int num)
{
    printf("Linea: %d Token: %s Lexema: %s\n", nline, tokens[num], lexema);
}

int main()
{
   /* declare a file pointer */
FILE    *infile;
char    *buffer;
long    numbytes;
 
/* open an existing file for reading */
infile = fopen("./demo.txt", "r");
 
/* quit if the file does not exist */
if(infile == NULL)
    return 1;
 
/* Get the number of bytes */
fseek(infile, 0L, SEEK_END);
numbytes = ftell(infile);
 
/* reset the file position indicator to 
the beginning of the file */
fseek(infile, 0L, SEEK_SET);	
 
/* grab sufficient memory for the 
buffer to hold the text */
buffer = (char*)calloc(numbytes, sizeof(char));	
 
/* memory error */
if(buffer == NULL)
    return 1;
 
/* copy all the text into the buffer */
fread(buffer, sizeof(char), numbytes, infile);
fclose(infile);
 
/* confirm we have read the file by
outputing it to the console */
printf("The file called demo.txt contains this text\n\n%s", buffer);
 


    int n = strlen(buffer);
    int i = 0;
    int edo = 1;
    while (i < n)
    {
        if(buffer[i] == '\n'){
            nline++;
            i++;
        }

        if(buffer[i] == ' '){
            i++;
        }
        switch (edo)
        {
        case 1:
            if (isalpha(buffer[i]))
            {
                edo = 2;
                lexema[ind++] = buffer[i++];
            }
            else
            {
                if (isdigit(buffer[i]))
                {
                    edo = 3;
                    lexema[ind++] = buffer[i++];
                }
                else
                {
                    if (buffer[i] == ';')
                    {
                        lexema[ind++] = buffer[i++];
                        //se encontro PYC
                        lexema[ind] = '\0';
                        imprimeToken(2);
                        edo = 1;
                        ind = 0;
                    }
                    else
                    {
                        if (buffer[i] == '=')
                        {
                            lexema[ind++] = buffer[i++];
                            edo = 4;
                        }
                        else
                        {
                            if (isOPAR(buffer[i]))
                            {
                                edo = 5;
                            }

                            else
                            {
                                if (isOPREL(buffer[i]))
                                {
                                    edo = 7;
                                }

                                else
                                {
                                    //Default ERR
                                    printf("%c\n", buffer[i++]);
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 2: // ID
            if (isalpha(buffer[i]) || isdigit(buffer[i]))
            {
                lexema[ind++] = buffer[i++];
            }
            else
            { //se encontro ID
                lexema[ind] = '\0';
                imprimeToken(4);
                edo = 1;
                ind = 0;
            }
            break;
        case 3:
            if (isdigit(buffer[i]))
            {
                lexema[ind++] = buffer[i++];
            }
            else
            { //se encontro NUM
                lexema[ind] = '\0';
                imprimeToken(5);
                edo = 1;
                ind = 0;
            }
            break;
        case 4:
            if (buffer[i] == '=')
            {
                lexema[ind++] = buffer[i++];
                //se encontro OPREL
                lexema[ind] = '\0';
                imprimeToken(0);
                edo = 1;
                ind = 0;
            }
            else
            { //se encontro ASG
                lexema[ind] = '\0';
                imprimeToken(1);
                edo = 1;
                ind = 0;
            }
            break;

        case 5: // OPAR
            if (isOPAR(buffer[i]))
            {
                lexema[ind++] = buffer[i++];
                edo = 6; // Pasamos al siguiente estado
            }
            else
            {
                lexema[ind] = '\0';
                imprimeToken(3);
                edo = 1;
                ind = 0;
            }
            break;

        case 6: // OPAR 2
            if ((buffer[i] == '+' && buffer[i] == lexema[ind - 1]) || (buffer[i] == '-' && buffer[i] == lexema[ind - 1]) || (buffer[i] == '*' && buffer[i] == lexema[ind - 1]))
            {
                lexema[ind++] = buffer[i++];
                // Termina
                lexema[ind] = '\0';
                imprimeToken(3);
                edo = 1;
                ind = 0;
            }
            else
            {
                lexema[ind] = '\0';
                imprimeToken(3);
                edo = 1;
                ind = 0;
            }
            break;

        case 7: // Primer estado/case donde se revisa OPREL
            printf("Case 7 goes here");
            /* if (isOPREL(buffer[i]))
            {

            } */

            break;
           
            case 8: //ASIG
            //TODO -- verificar con Sebas si asi esta bien
                if (buffer[i] == '=')
                {
                    lexema[ind++] = buffer[i++];
                    //Termina
                    lexema[ind] = '\0';
                    imprimeToken(1);
                    edo = 1;
                    ind = 0;
                }
                break;
        default:
            break;
        }
    }

    /* free the memory we used for the buffer */
    free(buffer);

    return 0;
}
