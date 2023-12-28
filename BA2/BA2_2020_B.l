%{
%}
%%

^[A-Za-z_]([A-Za-z_0-9]+)*[(]([A-Za-z]+([,][ ][A-Za-z]+)*)*[)] {printf("%s\n", yytext);}
.|\n {;}

%%
int main() {
	yylex();
	return(0);
}

int yywrap(){
    return 1;
}