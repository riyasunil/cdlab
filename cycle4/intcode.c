//1.headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void helper(char *inp, char op, char *reg){
    int i = 0;
    int j = 0;
    char temp[100];
    while (inp[i] != '\0')
    {
        if(inp[i] == op){
             printf("%c\t%c\t%c\t%c\n", op, * reg, inp[i - 1], inp[i + 1]);
            temp[j-1] = *reg;
            i+=2;
            (*reg)--;
            continue;
        }
        temp[j] = inp[i];
        i++;
        j++;

    }
    temp[++j] = '\0';
    strcpy(inp,temp);   
}