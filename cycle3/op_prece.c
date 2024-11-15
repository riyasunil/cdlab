//operator precedence parser:
// an operator precedence parser is genrally used to check the validity of a string in a language
// SHIFT: when the precedence relation is < (less than) or =, the parser shifts the current character from the input string onto the stack.
// REDUCE: When the precedence relation is >, the parser reduces the top portion of the stack based on a predefined rule 
// Acceptance: If both the stack and the input string reach the end simultaneously, the string is accepted.
// Error: If no valid action can be performed (no shift or reduce action is possible), the string is rejected.

//1. headers:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//2.declare variables:
int main(){
char stack[20], ip[20], opt[10][10] , ter[10];
int i,j,k;
int n;
int top = 0;
int col, row;

//3.init arrays:
for(i =0 ;i<10; i++){
    stack[i] = ' ';
    ip[i] = ' ';
    for(j = 0;j<10;j++){
        opt[i][j]= ' ';
    }
}
printf("Enter the no.of terminals :\n");
scanf("%d", &n);
printf("\nEnter the terminals :\n");
scanf("%s", &ter);

printf("\nEnter the table values :\n");
for (i = 0; i <n; i++) {
  for (j = 0; j < n; j++) {
    getchar(); 
    printf("Enter the value for %c %c:", ter[i], ter[j]);
    opt[i][j] = getchar(); 
  }
}
printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
for (i = 0; i < n; i++) {
  printf("\t%c",ter[i]);
}
printf("\n");
for (i = 0; i < n; i++) {
  printf("\n%c", ter[i]);
  for (j = 0; j < n; j++) {
    printf("\t%c", opt[i][j]);
  }
}

stack[top] = '$';
printf("\nEnter the input string:");
scanf("%s", ip);
i = 0;
printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
printf("\n%s\t\t\t%s\t\t\t", stack, ip);

while(i <= strlen(ip)){

    //main parsing loop
    for(k = 0; k<n;k++){
        if(stack[top] == ter[k]){
            col = k;
        }
        if(ip[i] == ter[k]){
            row = k;
        }
    }

    //parsing actions logic
    // ACCEPT
    if ((stack[top] == '$') && (ip[i] == '$')){
        printf("String is accepted");
        break;
    }
    // SHIFT
    else if(opt[col][row] == '<' || opt[col][row] == "="){
        stack[++top] = opt[col][row];
        stack[++top] = ip[i];
        printf( "shift %c", ip[i]);
        i++;
    }
    //REDUCE
    else{
        if(opt[col][row] == '>'){
            while (stack[top] != '<')
            {
                --top;
            }
            top = top-1;
            printf("reduce");
            
        }else{
            printf("string not accepted");
            break;
        }
    }
    printf("\n");
    for (k = 0; k <= top; k++) {
      printf("%c", stack[k]);
    }printf("\t\t\t");
    for (k = i; k < strlen(ip); k++) {
      printf("%c", ip[k]);
    }
    printf("\t\t\t");
}
getchar();
}