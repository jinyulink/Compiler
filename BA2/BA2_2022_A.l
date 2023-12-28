%{
    // 2022 Compiler BA2 A 
    #include<stdio.h>
%}

%%
"//"    {printf("#");}
"/*"    {printf("\"\"\"");}
"*/"    {printf("\"\"\"");}
"cout << "  {printf("print(");}
" << endl;"  {printf(")");}
"if(true) {"    {printf("if True:");}
"\n}"
.   {printf("%s", yytext);}
%%
int main(){
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
