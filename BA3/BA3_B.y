%{
#include <stdio.h>
#define STACK_SIZE 10

void yyerror(const char *s);
int stop = 0;
int i;

struct stack {
    int data[STACK_SIZE];
    int top;
};

typedef struct stack stack_t;
stack_t stack;

int isEmpty() {
    return stack.top == 0;
}

int isFull() {
    return stack.top == STACK_SIZE;
}

void push(int i) {
    if(stop==1) return 0;
    if (isFull()) {
        printf("Runtime Error: The push will lead to stack overflow.\n");
        stop = 1;
    }
    stack.data[stack.top++] = i;
}

int pop() {
    if(stop==1) return 0;
    if (isEmpty()) {
        printf("Runtime Error: The pop will lead to stack underflow.\n");
        stop = 1;
    }
    return stack.data[--stack.top];
}

void dump() {
    if(stop==1) return;
    printf("The contents of the stack are: ");
    for (i = 0; i < stack.top; i++) {
        printf("%d ", stack.data[i]);
    }
    printf("\n");
}

%}

%token NUMBER ADD SUB MUL DIV

%%

expressions : 
            | expressions expression
            ;

expression  : NUMBER  { push($1); dump(); }
            | ADD     { int a = pop(); int b = pop(); push(b + a); dump(); }
            | SUB     { int a = pop(); int b = pop(); push(b - a); dump(); }
            | MUL     { int a = pop(); int b = pop(); push(b * a); dump(); }
            | DIV     { int a = pop(); int b = pop(); push(b / a); dump(); }
            ;

%%

int main() {
    stack.top = 0;
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}