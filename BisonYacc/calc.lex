/* Lexer au format "flex"
 * cf. http://flex.sourceforge.net/
 */

/* preambule */
%{

#include "calc.tab.h"  /* fichier produit par "bison" contenant type des tokens */
#include <stdlib.h>

%}

/* expressions regulieres */

spaces     [ \t\n]+

digit      [0-9]
integer    {digit}+
var        "#"{integer}

/* Production des tokens associes aux expressions regulieres */
%%

{spaces}  { /* On ignore */ }

{integer}    {
        yylval.val=atoi(yytext);
        /* decommenter la ligne ci-dessous pour voir les nombres reconnus */
        /* printf("yylval=%d|%s|\n", yylval.val,yytext) ; */
        return INT;
}

{var} {
        yylval.val=atoi(yytext+1); 
        return VAR;
}

"+"   return PLUS;
"-"   return MINUS;

"*"   return MULT;
"/"   return DIV;

"("   return OPAR;
")"   return CPAR;

"?"   return QUEST;

. { 
        printf("ERROR: unknown recognized token %s\n", yytext);
        exit(1);
}
