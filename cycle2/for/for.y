%{
    #include <stdio.h>
    int valid = 1;
    int yyerror(char *s);
    int yylex(void);
%}

%token FOR PARAS OPERAND OPERATOR SEMICOLON COMMA NEWLINE

%%
start : FOR PARAS A B PARAS NEWLINE;
A: OPERAND OPERATOR OPERAND SEMICOLON| OPERAND OPERATOR OPERAND A| SEMICOLON;
B:  OPERAND OPERATOR OPERAND | OPERAND OPERATOR OPERAND SEMICOLON| OPERAND OPERATOR OPERAND COMMA B|;
%%

int yyerror(char *s){
    printf("error %s\n", s);
    valid = 0;
    return 1;
}

int main(){
    printf("enter string");
    yyparse();
    if(valid){
        printf("valif for loop");
    }
}