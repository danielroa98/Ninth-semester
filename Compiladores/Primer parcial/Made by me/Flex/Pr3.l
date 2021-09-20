/* Declaraciones */

%option noyywrap
/* Buscará la palabra amor y escribirá odio */
ws [ ]
%%
{ws}amor{ws} 	printf("odio");

%%

int main(void){
   yylex();
}
