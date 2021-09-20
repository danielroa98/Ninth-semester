/*

Miembros del Equipo 5:

- Antonio Junco de Haas - A01339695
- Daniel Roa - A01021960
- Sergio Hernández Castillo - A01025210
- Sebastián Vives Faus - A01025211


Instrucciones

OPREL    <, <=, >, >=, == -> Sergio
ASIG        = --> Roa
OPAR      +, -, *, /, %, **, ++, -- -> Sebas
ID             letra(letra|digito)+ ----> Done
ENT          digito+
REAL        digito+   ( .digito+(E(+|-)?digito+) | .digito+ | E(+|-)?digito+ )
ERR         cualquier cosa que no empate con ningún token (agrupado en el mismo
lexema si son varios símbolos concatenados) p.e. @#$+  debe quedar ERR @#$ OPAR
+

*/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tokens[8][6] =
	{"OPREL", "ASIG", "PYC", "OPAR", "ID", "ENT", "REAL", "ERR"};
char lexema[30];

char operaciones[6] = {'+', '-', '*', '/', '%'};
char comparaciones[4] = {'<', '>'};

int ind = 0;
int nline = 0;

bool isOPAR(char x) {
	for (int i = 0; i < 4; i++) {
		if (x == operaciones[i]) {
			return true;
		}
	}

	return false;
}

bool isOPREL(char x) {
	for (int i = 0; i < 3; i++) {
		if (x == comparaciones[i]) {
			return true;
		}
	}

	return false;
}

void imprimeToken(int num) {
	printf("Linea: %d Token: %s Lexema: %s\n", nline, tokens[num], lexema);
}

int main() {
	/* declare a file pointer */
	FILE *infile;
	char fileName[100];
	char *buffer;
	long numbytes;

	/* open an existing inputted file for reading */
	printf("Insert file name here\n");
  gets(fileName);
  infile = fopen(fileName, "r");

	/* quit if the file does not exist */
	if (infile == NULL)
		return 1;

	/* Get the number of bytes */
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);

	/* reset the file position indicator to
the beginning of the file */
	fseek(infile, 0L, SEEK_SET);

	/* grab sufficient memory for the
buffer to hold the text */
	buffer = (char *)calloc(numbytes, sizeof(char));

	/* memory error */
	if (buffer == NULL)
		return 1;

	/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);

	/* confirm we have read the file by
outputing it to the console */
	printf("The file called %s contains this text\n\n%s\n\n", fileName, buffer);

	int n = strlen(buffer);
	int i = 0;
	int edo = 1;

	bool err = false;
	bool ent_real = false;

	while (i < n) {
		if (buffer[i] == '\n') {
			nline++;
			i++;
		}

		if (buffer[i] == ' ') {
			i++;
		}
		switch (edo) {
		case 1:
			if (isalpha(buffer[i])) {
				if (err) {
					imprimeToken(7);
					ind = 0;
					err = 0;
				}
				edo = 2;
				lexema[ind++] = buffer[i++];
			} else {
				if (isdigit(buffer[i])) {
					if (err) {
						imprimeToken(7);
						ind = 0;
						err = 0;
					}

					edo = 3;
					lexema[ind++] = buffer[i++];
				} else {
					if (buffer[i] == ';') {
						if (err) {
							imprimeToken(7);
							ind = 0;
							err = 0;
						}

						lexema[ind++] = buffer[i++];
						// se encontro PYC
						lexema[ind] = '\0';
						imprimeToken(2);
						edo = 1;
						ind = 0;
					} else {
						if (buffer[i] == '=') {
							if (err) {
								imprimeToken(7);
								ind = 0;
								err = 0;
							}

							lexema[ind++] = buffer[i++];
							edo = 4;
						} else {
							if (isOPAR(buffer[i])) {
								if (err) {
									imprimeToken(7);
									ind = 0;
									err = 0;
								}
								edo = 5;
							}

							else {
								if (isOPREL(buffer[i])) {
									if (err) {
										imprimeToken(7);
										ind = 0;
										err = 0;
									}

									lexema[ind++] = buffer[i++];
									edo = 7;
								}

								else {
									// Default ERR
									// printf("%c\n", buffer[i++]);
									if (buffer[i] == ' ') {
										ind++;
										i++;
									} else {
										err = 1;
										lexema[ind++] = buffer[i++];
									}
								}
							}
						}
					}
				}
			}
			break;
		case 2: // ID
			if (isalpha(buffer[i]) || isdigit(buffer[i])) {
				lexema[ind++] = buffer[i++];
			} else { // se encontro ID
				lexema[ind] = '\0';
				imprimeToken(4);
				edo = 1;
				ind = 0;
			}
			break;
		case 3:
			if (isdigit(buffer[i])) {
				lexema[ind++] = buffer[i++];
			}

			else if (buffer[i] == '.') {
				lexema[ind++] = buffer[i++];
				ent_real = 1;
			}

			else { // se encontro NUM
				lexema[ind] = '\0';
				if (ent_real) {
					imprimeToken(6);
				} else {
					imprimeToken(5);
				}
				ent_real = 0;
				edo = 1;
				ind = 0;
			}
			break;
		case 4:
			if (buffer[i] == '=') {
				lexema[ind++] = buffer[i++];
				// se encontro OPREL
				lexema[ind] = '\0';
				imprimeToken(0);
				edo = 1;
				ind = 0;
			} else { // se encontro ASG
				lexema[ind] = '\0';
				imprimeToken(1);
				edo = 1;
				ind = 0;
			}
			break;

		case 5: // OPAR
			if (isOPAR(buffer[i])) {
				lexema[ind++] = buffer[i++];
				edo = 6; // Pasamos al siguiente estado
			} else {
				lexema[ind] = '\0';
				imprimeToken(3);
				edo = 1;
				ind = 0;
			}
			break;

		case 6: // OPAR 2
			if ((buffer[i] == '+' && buffer[i] == lexema[ind - 1]) ||
				(buffer[i] == '-' && buffer[i] == lexema[ind - 1]) ||
				(buffer[i] == '*' && buffer[i] == lexema[ind - 1])) {
				lexema[ind++] = buffer[i++];
				// Termina
				lexema[ind] = '\0';
				imprimeToken(3);
				edo = 1;
				ind = 0;
			} else {
				lexema[ind] = '\0';
				imprimeToken(3);
				edo = 1;
				ind = 0;
			}
			break;

		case 7: // Estado/case donde se revisa OPREL
			if (buffer[i] == '=') {
				lexema[ind++] = buffer[i++];
				// se encontro OPREL
				lexema[ind] = '\0';
				imprimeToken(0);
				edo = 1;
				ind = 0;
			}

			else {
				lexema[ind] = '\0';
				imprimeToken(0);
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
