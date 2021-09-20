/* Definition section has one variable */
%{
    int count = 0;
%}

/* Rule section has three rules */
/* First rule matches capital letter */
/* Second rule matches with any character except newline */
/* Third rule does not take input after the enter */
%%
[A-Z]   {printf("%s capital letter\n", yytext);
        count++;}
.       {printf("%s not a capital letter\n", yytext);}
\n      {return 0;}
%%

int yywrap(){}
int main(){
    yylex();
    printf("\nNumber of Capital letters "
    "in the given input - %d\n", count);

    return 0;
}