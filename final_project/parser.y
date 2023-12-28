%{
    #include "ast.h"
    extern struct Node* root;
%}

%union {
    int ival;
    char* id;
    struct Node* node;
}

%token<ival> NUMBER
%token<ival> BOOLEAN
%token<id> ID
%token PRINT_NUM PRINT_BOOL DEFINE LAMBDA IF MOD AND OR NOT

// return int or BOOLEAN
%type<node> program stmts stmt print_stmt exp exps num_op logical_op def_stmt variable 
%type<node> fun_exp fun_ids fun_body fun_call params param fun_name 
%type<node> if_exp test_exp then_exp else_exp
 
%%
program     : stmts                         { root = $1; }  
            ;

stmts       : stmt stmts                    { $$ = create_node($1, $2, 'T'); }
            | stmt                          { $$ = create_node($1, NULL, 'T'); }
            ;

stmt        : exp                           { $$ = $1; }
            | def_stmt                      { $$ = $1; }
            | print_stmt                    { $$ = $1; }
            ;

print_stmt  : '(' PRINT_NUM exp ')'         { $$ = create_node($3, NULL, 'P'); } 
            | '(' PRINT_BOOL exp ')'        { $$ = create_node($3, NULL, 'p'); }
            ; 

exp         : BOOLEAN                       { $$ = create_node(NULL, NULL, 'B'); $$->value = $1; }
            | NUMBER                        { $$ = create_node(NULL, NULL, 'I'); $$->value = $1; }
            | variable                      { $$ = $1;}
            | num_op                        { $$ = $1;}
            | logical_op                    { $$ = $1;}
            | fun_exp                       { $$ = $1;}
            | fun_call                      { $$ = $1;}
            | if_exp                        { $$ = $1;}
            ;

exps        : exp exps                      { $$ = create_node($1, $2, 'E'); }
            | exp                           { $$ = create_node($1, NULL, 'E'); }
            ;

num_op      : '(' '+' exp exps ')'          { $$ = create_node($3, $4, '+');}
            | '(' '-' exp exp ')'           { $$ = create_node($3, $4, '-'); }    
            | '(' '*' exp exps ')'          { $$ = create_node($3, $4, '*'); }
            | '(' '/' exp exp ')'           { $$ = create_node($3, $4, '/'); }
            | '(' MOD exp exp ')'           { $$ = create_node($3, $4, '%'); }
            | '(' '>' exp exp ')'           { $$ = create_node($3, $4, '>'); }
            | '(' '<' exp exp ')'           { $$ = create_node($3, $4, '<'); }
            | '(' '=' exp exps ')'          { $$ = create_node($3, $4, '='); }
            ;

logical_op  : '(' AND exp exps ')'          { $$ = create_node($3, $4, '&'); }
            | '(' OR exp exps ')'           { $$ = create_node($3, $4, '|'); } 
            | '(' NOT exp ')'               { $$ = create_node($3, NULL, '^');}
            ;

def_stmt    : '(' DEFINE variable exp ')'   { $$ = create_node($3, $4, 'D'); }
            ;

variable    : ID                            { $$ = create_node(NULL, NULL, 'V'); $$->id = $1; }
            ;

// 創建一個函數節點，其中包含參數列表和函數體。
fun_exp     : '(' LAMBDA '(' fun_ids ')' fun_body ')'  { $$ = create_node($4, $6, 'F');}
            ;

// 在 (funx  (x y) (+ x y)) 中，x 和 y 將被創建為函數參數節點。
fun_ids     : ID fun_ids                    { struct Node* tmp = create_node(NULL, NULL, 'V'); tmp->id = $1; $$ = create_node(tmp, $2, 'S'); }
            |                               { $$ = NULL; }
            ;

// 在 (lambda (x) (+ x 1)) 中，(+ x 1) 是函數體。
fun_body    : exp                           { $$ = $1;}
            ;

// 執行函數調用，可以是匿名函數或已命名的函數。
// (add1 5) 會創建一個函數調用節點，其中 add1 是函數名，5 是傳遞給函數的參數。
fun_call    : '(' fun_exp params ')'        { $$ = create_node($3, $2, 'C');}
            | '(' fun_name params ')'       { $$ = create_node($3, $2, 'C');}
            ;

// 定義傳遞給函數的參數。
// 在 (add1 5) 中，5 被創建為參數節點。
params      : param params                  { $$ = create_node($1, $2, 'A');}
            |                               { $$ = NULL;}
            ;

// 定義單個參數。
// 在 (add1 5) 中，5 是一個單獨的參數。
param       : exp                           { $$ = $1;}
            ;

// 定義已命名的函數名稱。
// 在 (add1 5) 中，add1 是函數名稱。
fun_name    : ID                            { $$ = create_node(NULL, NULL, 'V'); $$->id = $1; }
            ;

if_exp      : '(' IF test_exp then_exp else_exp ')'  { struct Node* tmp = create_node($4, $5, 'X'); $$ = create_node($3, tmp, 'G'); }
            ;

test_exp    : exp                           { $$ = $1; }
            ;

then_exp    : exp                           { $$ = $1; }
            ;

else_exp    : exp                           { $$ = $1; }
            ;

%%

int main(void) {
    yyparse();
    traverseAST(root);
    return 0;
}
