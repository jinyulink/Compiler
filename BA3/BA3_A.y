%{
    #include <stdio.h>
    void yyerror(const char *s);
    int valid = 1;
%}
%union
{
    float fval;
}
%token PLUS MINUS MULTIPLY DIVIDE
%token INVALID
%token <fval> NUMBER
%type  <fval>  expr term factor

%left PLUS MINUS
%left MULTIPLY DIVIDE
%%
line    : expr {if(valid) printf("%.3f\n", $1);
                else printf("Invalid Value");
               } 
        ;
expr    : expr PLUS term    { $$ = $1 + $3; }
        | expr MINUS term   { $$ = $1 - $3; }
        | term              { $$ = $1; }
        ;
term    : term MULTIPLY factor  { $$ = $1 * $3; }
        | term DIVIDE factor    { if($3 == 0.0) valid = 0; else $$ = $1 / $3; }
        | factor                { $$ = $1; }
        ;
factor  : NUMBER               { $$ = $1; }
        | INVALID              {valid = 0;}
        ;
%%
int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    // fprintf(stderr, "%s\n", s);
}   