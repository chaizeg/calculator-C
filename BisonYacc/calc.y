/* Parser au format bison
 * cf.  http://www.gnu.org/software/bison/manual/
 */

/* preambule */
%{

#include <stdio.h>
#include "list.h"

static list l; /* variable globale au lieu de attribut hérité */
%}

/* Types de l'attribut synthetisé */
%union {
int val ; /* pour expression */
}

/* Terminaux */
/* syntaxe concrète des terminaux définie dans fichier "calc.lex" */
%token <val> INT
%token <val> VAR
%token PLUS MINUS MULT DIV
%token OPAR CPAR QUEST

/* Attributs associées aux Non-Terminaux */
%type <val> exp

/* Niveau de précédence (du moins prioritaire au plus prioritaire)
   avec associativité des symboles
 */
%left PLUS MINUS
%left MULT DIV
%precedence NEG  /* Token "virtuel" utilisé uniquement pour précédence du moins unaire */

/* Axiome */
%start input

/* Règles de la grammaire attribuée */
%%

input:
    /* epsilon */   { l=empty(); }
  | input exp QUEST { append(l,$2); }
  ;

exp:
    INT      { $$=$1; }
  | VAR      { $$=pick(l,$1); } 
  | exp PLUS exp  { $$=$1+$3; }
  | exp MINUS exp { $$=$1-$3; }
  | exp MULT exp  { $$=$1*$3; }
  | exp DIV exp   { $$=$1/$3; }
  | MINUS exp %prec NEG  { $$=-$2; }  /* ici: MINUS a la précédence de NEG ! */
  | OPAR exp CPAR  { $$=$2; }
  ;

%%

int yyerror(char *s) {
        printf("ERROR: %s\n",s);
}

int main(void) {
        printf("// Mini-calculator (programmed in Bison).\n//\n") ;
        printf("// Enter below a sequence of integer computations (using infix notation).\n");
        printf("// Each computation must end with '?'.\n") ;
        printf("// Type Ctrl-D to quit.\n") ;
        yyparse();
        printf("// End of Input: Bye !\n") ;
        destruct(&l);
}
