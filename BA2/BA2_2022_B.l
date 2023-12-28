%{
    #include<stdio.h>
%}

%%
[a-zA-Z]+[ ]+[A-Z][a-z]+-[A-Z][a-z]+  { printf("%s\n", yytext); }  /* Name */
[a-zA-Z][0-9]{9}                      { printf("identity number: %s\n", yytext); }  /* Identity Number */
[0-9]+@[a-z]+(\.[a-z]+)+              { printf("email: %s\n", yytext); }  /* Email */
[0-9]{4}\/[0-9]{2}\/[0-9]{2}            { printf("birthday: %s\n", yytext); }  /* Birthday */
\+886[0-9]{9}                         { printf("phone: %s\n", yytext); }  /* Phone */
\n                                    { printf("\n"); }  /* Newline for separating entries */
%%

int main(){
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}