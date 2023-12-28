%{
int indent = 0; // 缩进级别计数器

void print_indent() {
    for (int i = 0; i < indent; ++i) {
        printf("\t");
    }
}
%}

%%
"{"         { indent++; printf("{\n"); print_indent(); }
"}"         { indent--; printf("\n"); print_indent(); printf("}"); }
"\n"        { printf("\n"); print_indent(); }
[^\n{}]+    { printf("%s", yytext); }

%%

int main(int argc, char **argv)
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
