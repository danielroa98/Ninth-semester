# In order to run Flex on any named file
lex <filename>.l

# After the C file is generated, run
gcc lex.yy.c

# Afterwards, run the compiled program
./a.out