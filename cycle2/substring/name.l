/*lex program to exclude words with a certain substring*/

/*lex takes a description of a languages lexical structre in the form of regex and generates a c program that can identify these rules on the provided input */

/*defenitions section : incldue c code, declare variables, functions, etc */
%{
#include <stdio.h>
#include <string.h>

char name[100];
char prefix[100];

void isvalid(const char *input_string){
    if (strstr(input_string, prefix) == NULL){
        printf("%s is recognized\n", input_string);
    }else{
        printf("%s is not recognized\n", input_string);
    }
}

%}

/*rules section */
/*yytext is a special lex variable that holds the text matched by the current rule*/
%%
[A-Za-z]+ {isvalid(yytext);}
\n {}
. {}
%%

/*user code section*/

int main(){
    char name[100];
    printf("Enter the name: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = 0; //strcspn returns the index of the first matched char in st1 that is also in st2.
    int plen = 4;
    strncpy(prefix, name, plen); // dest, source, n
    prefix[plen] = '\0'; //adding null terminator

    printf("Enter input strings (Ctrl+D to stop):\n");
    yylex();
    return 0;


}

int yywrap(){
    return 1;
}