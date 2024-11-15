%{
#include <stdio.h>
int valid = 1;
int yyerror();
int yylex();
%}

%token digit letter

%%
start : letter s
s: letter s | digit s | ;
%%

int yyerror(){
    printf("not valid \n");
    valid = 0;
    return 0;
}

int main(){
    printf("\nEnter a name to test for identifier: ");
    yyparse();
    if(valid){
        printf("\nIt is an identifier!\n");
    }
}
