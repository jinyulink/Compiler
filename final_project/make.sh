bison -d parser.y
flex scanner.l
gcc -c ast.c
gcc -c parser.tab.c
gcc -c lex.yy.c
gcc ast.o lex.yy.o parser.tab.o -lfl
rm lex.yy.c lex.yy.o parser.tab.c parser.tab.h parser.tab.o ast.o

for file in ./hidden_test_data/*
do
    echo "Testing $file"
    ./a.out < $file
    echo "-----------------------------------"
done
