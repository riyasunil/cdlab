%{
    #include "y.tab.h" 
%}

/* Rules Section */
%%
for            return FOR;
[\(\)]         return PARAS;
[a-zA-Z0-9]*  return OPERAND;
"="|"<"|">"|">="|"<="|"=="|"++"|"--"	return OPERATOR;
\;             return SEMICOLON;
,              return COMMA;
\n             return NEWLINE;
.              ;    
%%

int yywrap(){
    return 1;
}
