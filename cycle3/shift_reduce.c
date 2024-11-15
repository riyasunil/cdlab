/*
bottom-up parser
used in syntax analysis
constrcuts a parse tree for the input string
by shifting input symbols onto a stack
then reduce them based on a grammar 
until the start symbol is derived

Actions:

Shift: Move the next symbol from the input buffer to the stack.
Reduce: Replace a sequence of symbols on the stack (called a handle) with a non-terminal, based on a grammar rule.
Accept: Parsing is successful; the input string is accepted.
Error: The input string is not valid according to the grammar.

Advantages of Shift-Reduce Parsing
------------------------------------
Simple and Efficient: Commonly used in tools like yacc and bison.
Works for Many Grammars: Can handle most context-free grammars.

Limitations
-----------
Conflicts:

Shift/Reduce Conflict: The parser cannot decide whether to shift or reduce.
Reduce/Reduce Conflict: The parser cannot decide which rule to reduce.
These conflicts typically occur in ambiguous grammars.

Restricted Grammars:

It requires the grammar to be LR(k) or a similar form, which may need transformations.

Variants
--------
SLR Parser (Simple LR): Simplest version of shift-reduce parsing.
LR Parser: More powerful, handles a wider range of grammars.
LALR Parser (Lookahead LR): Combines the simplicity of SLR and the power of LR.
*/

//1.header
#include <stdio.h>
#include <string.h>

//2.defenitions
#define MAX_INPUT 100
#define MAX_STACK 100

void check();

char buffer[MAX_INPUT], stack[MAX_STACK], action[20];
int input_len, top = -1;


//3.main function
int main(){
    printf("GRAMMAR is:\nE -> E+E | E*E | (E) | id\n");
    printf("Enter input string: ");
    scanf("%s", buffer);
    input_len = strlen(buffer);
    printf("\nStack\t\tInput\t\tAction\n");

    for(int i = 0; i<input_len;i++){
        if(buffer[i] == 'i' && buffer[i+1] == 'd'){
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top+1]= '\0';
            printf("$%s\t\t%s$\t\tSHIFT->id\n", stack, buffer + i + 2); //shifted `id` onto stack
            check(); // check if whatevrs in the stack rn can be reduced
            i++; //skip the d
        }
        else{
            stack[++top] = buffer[i];
            stack[top+1] = '\0';
             printf("$%s\t\t%s$\t\tSHIFT->%c\n", stack, buffer + i + 1, buffer[i]);
             check();
        }
    }

    if (top == 0 && stack[0] == 'E') {
        printf("\nInput string is VALID.\n");
    } else {
        printf("\nInput string is INVALID.\n");
    }

    return 0;
}

//4. check function
void check(){
    int i,j, handle_size;
    char *handle = NULL;

    while(1){
        if(top>=1 && stack[top-1] == 'i' && stack[top] =='d'){
            handle = "id";
            handle_size = 2;
        }
        else if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '+' && stack[top] == 'E') {
            handle = "E+E";
            handle_size = 3;
        } else if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '*' && stack[top] == 'E') {
            handle = "E*E";
            handle_size = 3;
        } else if (top >= 2 && stack[top-2] == '(' && stack[top-1] == 'E' && stack[top] == ')') {
            handle = "(E)";
            handle_size = 3;
        } else {
            return;  // No reduction possible
        }

        //perform reduction:
        top -= handle_size -1;
        stack[top] = 'E';
        stack[top+1] ='\0';
        printf("$%s\t\t%s$\t\tREDUCE->%s\n", stack, buffer + strlen(buffer), handle);
    }
}