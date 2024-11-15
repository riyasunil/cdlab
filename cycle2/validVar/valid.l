/* defenitions section */
%{
#include "y.tab.h"
%}
/*rules section*/
%%
[a-zA-z_][a-zA-z0-9]* {return letter;}
[0-9] {return digit;}
. {return yytext[0];}
\n {return 0;}
%%
/*user code section*/
int yywrap(){
    return 1;
}