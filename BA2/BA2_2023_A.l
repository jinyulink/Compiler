%{
    // 2023 Compiler BA2 A 
    #include<stdio.h>
%}

%%
^[0-9]+"."[0-9]*$ {printf("%s FLOAT\n", yytext);}
^[0-9]*"."[0-9]+$ {printf("%s FLOAT\n", yytext);}
^\"[^\"\n]*\"$ { printf("%s STRING\n", yytext); }
^\'[^\'\n]*\'$ { printf("%s STRING\n", yytext); }
^[0-9]+$ {printf("%s INTERGER\n", yytext);}
^[a-zA-Z_][a-zA-Z_0-9]*$ { printf("%s VARIABLE\n", yytext); }
.|\n {;}
%%
int main(){
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}


// \"[^\"\n]*\" { printf("%s STRING\n", yytext); }
// \'[^\'\n]*\' { printf("%s STRING\n", yytext); }

// [0-9]+"."[0-9]+ { printf("%s FLOAT\n", yytext); }

// [0-9]+ { printf("%s INTEGER\n", yytext); }

