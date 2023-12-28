%{
    #include <stdio.h>
    #include <stdbool.h>
    void yyerror(char *s);
%}

%token OPEN_ANGLE CLOSE_ANGLE SLASH AND OR NOT TRUE FALSE 

%%

start   : tag { printf("%s\n", $1 ? "true":"false"); }
        ;

tag     : boolean_tag
        | logic_tag
        ;

boolean_tag
        : OPEN_ANGLE TRUE SLASH CLOSE_ANGLE { $$ = true; }
        | OPEN_ANGLE FALSE SLASH CLOSE_ANGLE { $$ = false; }
        ;

logic_tag
        : OPEN_ANGLE AND CLOSE_ANGLE tag_list OPEN_ANGLE SLASH AND CLOSE_ANGLE
        { 
            $$ = true;
            for (int i = 0; i < $4.count; ++i) {
                if (!$4.values[i]) {
                    $$ = false;
                    break;
                }
            }
        }
        | OPEN_ANGLE OR CLOSE_ANGLE tag_list OPEN_ANGLE SLASH OR CLOSE_ANGLE
        { 
            $$ = false;
            for (int i = 0; i < $4.count; ++i) {
                if ($4.values[i]) {
                    $$ = true;
                    break;
                }
            }
        } 
        | OPEN_ANGLE NOT CLOSE_ANGLE tag OPEN_ANGLE SLASH NOT CLOSE_ANGLE { $$ = !$4; }
        ;

tag_list
        : tag
        {
            $$ = (struct tag_list*)malloc(sizeof(struct tag_list));
            $$->values = (bool*)malloc(sizeof(bool));
            $$->values[0] = $1;
            $$->count = 1;
        }
        | tag_list tag
        {
            $$ = $1;
            $$->values = (bool*)realloc($$->values, ($$->count + 1) * sizeof(bool));
            $$->values[$$->count] = $2;
            $$->count++;
        }
        ;

%%

int main(int argc, char **argv) {
    yyparse();
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}