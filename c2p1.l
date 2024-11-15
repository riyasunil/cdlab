%{
#include <stdio.h>
#include <string.h>

char name[5];  // To hold the first four characters of the name
int ignore_flag = 0; // Flag to indicate if string should be ignored

void update_ignore_flag(char *input) {
    // Check if the input string contains the first four characters of the name
    if (strstr(input, name) != NULL) {
        ignore_flag = 1;
    } else {
        ignore_flag = 0;
    }
}
%}

%%
.*\n {
    // Check if the input line contains the first four characters of the name
    update_ignore_flag(yytext);
    if (!ignore_flag) {
        printf("Valid String: %s", yytext);
    }
}
%%

int main() {
    printf("Enter your name (at least 4 characters): ");
    scanf("%4s", name);  // Read the first four characters of the name
    printf("Ignoring strings that contain the substring: %s\n", name);
    yylex();  // Start processing input strings
    return 0;
}


/*
mec@cc-x-x:~/CD-S7/Cycle_2_q1$ lex name.l
mec@cc-x-x:~/CD-S7/Cycle_2_q1$ gcc lex.yy.c -o name -ll
mec@cc-x-x:~/CD-S7/Cycle_2_q1$ ./name
Enter your name (at least 4 characters): gopika
Ignoring strings that contain the substring: gopi
Valid String: ka
vaidehi
Valid String: vaidehi
gopi
hello
Valid String: hello

*/    
