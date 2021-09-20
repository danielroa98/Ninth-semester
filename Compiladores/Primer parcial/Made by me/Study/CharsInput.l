/* Declaring two counterf one for the lines and another for character */
%{
    // This are to count upper and lower cases
    int num_lowers = 0;
    int num_uppers = 0;
    // This are to count the lines and the chars
    int num_lines = 0;
    int num_chars = 0;
%}

/* Rule 1 - counts the number of lines */
/* Rule 2 - counts the number of characters */
/* Rule 3 - specifies when to stop taking the input */
%%
[A-Z]   ++num_uppers;
[a-z]   ++num_lowers;
\n      ++num_lines;
.       ++num_chars;
end     return 0;
%%

/* User code section */
int yywrap(){}
int main(int argc, char **argv){
    yylex();
    printf("Number of lines is %d, number of chars is %d\n",
            num_lines, num_chars);

    return 0;
}
