// implementation of a lexical analyser

/*
global variables: line[100] => buffer to store each line read from the input file
helper functions:
    -> check if character is an operator +, -, *, /, =. if yes, return 1 else 0
    -> check if char is delimiter {, }, (, ), [, ], ,, ;. if yes, return 1 else 0
    -> check if string is a keyword against the 32 predefined keywords in c (for, if, else ...) return 1 if yes else 0
main function:
    ->file handling -> open input.txt and read code line by line using fgets()
    ->handle comments  ->  if line contains `//` , skip from there to the end of that line, if `/*` is found, skip till comment end is found
    ->tokenization : (each line is processed as follows):
        1. init:
            buffer (token) is inited to build tokens ( identifiers or keywords)
            index = 0 for managing token
        2. char by char parsing:
            for c in line:
                if c is operator call helper
                if c is delimiter call helper
                if c is whitespace or \n -> marks end of potential token
                if valid token exists:
                    call is_keyword
                    if not keyword, classify as identifier 
                reset the token buffer and index
                if char is not op, delimiter or whitespace:
                    append to token to continue building potential keyword or identitfier
*/

//1.headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2.global variable
char line[100];

//3.helper functions
int is_op(char c){
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
        printf("%c - Operator\n", c);
        return 1;
    default:
        break;
    }
    return 0;
}

int is_delim(char c){
    switch (c)
    {
    case '{':
        case '}':
        case '(':
        case ')':
        case '[':
        case ']':
        case ',':
        case ';':
            printf("%c - Delimiter\n", c);
            return 1;
    default:
        break;
    }
    return 0;
}

int is_keyword(char buffer[]){
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
    int i;
    for(i=0;i<32;i++){
        if (strcmp(keywords[i], buffer) ==0){
            return 1;
        }
    }
    return 0;
}

//4.main function
void main()
{
    int i,j;
    char c;
    FILE *f = fopen("input.txt", "r");
    while(fgets(line, sizeof(line), f)){
        //check for //
        int flag1 = 0;
        for (i=0;i<strlen(line); i++){
            if (line[i] == '/' && line[i+1] == '/'){
                flag1 = 1;
                break;
            }
        }
        if(flag1){
            continue; //skip the rest of the line, so here if flag == 1 and it enters the if, we go back to the while loop and get the next line
        }

        //check for multiline comments
        int flag2 = 0;
        for(i=0;i<strlen(line);i++){
            if(line[i] == '/' && line[i+1] == '*'){
                while(fgets(line, sizeof(line), f)){
                    for (j=0;j<strlen(line);j++){
                        if(line[i] == '*' && line[i+1] =='/'){
                            flag2 = 1;
                        }
                        if(flag2){
                            break;
                        }
                    }
                }
            }
        }
        if(flag2){
            continue;
        }
        printf("\n%s\n", line);

        char token[100];
        int index = 0;
        strcpy(token, "");

        for(i=0;i<strlen(line); i++){
            if(is_delim(line[i]) || is_op(line[i]) || line[i] == ' ' || line[i] == "\n" || line[i] == "\t"){
                if(strcmp(token, "") !=0) //if there are stuff already in the token
                {
                    if (is_keyword(token)){
                        printf("%s - Keyword\n", token);
                    }
                    else{
                        printf("%s - Identifier\n", token);
                    }
                    strcpy(token, ""); //reset it back 2 empty
                    index = 0; //reset index
                }
            }else{
                //it is a token (keyword or identifier)
                token[index++] = line[i];
                token[index] = '\0';
            }
        }
    } //end of outermost while
    fclose(f);
}