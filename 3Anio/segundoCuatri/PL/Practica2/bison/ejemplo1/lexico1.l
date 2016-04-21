%{
#include <stdio.h>

#include "ejemplo1.h"
#include "ejemplo1.tab.h"

extern char *progname;
extern int lineno;
%}
/* definicion regular */

numero   [0-9]
  	
%%
[ \t] 		{ ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+  {
                                    sscanf(yytext,"%lf",&yylval);
                                    return NUMBER; 
                                    }

\n      {lineno++; return '\n';}

.       {return yytext[0];}
%%

