/* Implementation of a calculator in prefix notation */

#include <stdio.h>
#include <assert.h>
#include "lexer.h"
#include "list.h" 

void parse_exp(list l, int *v) {
        token current = next(v);
	int v1 = 0, v2 =0;
        switch (current) {
        case INT:
                break;
       	case VAR:
	  if (*v <= length(l)){
	    *v = pick(l, *v);}
	  else{ unexpected(current, *v, "exp");} //pour récupérer l'élément indiqué par #*v
	  break;
	case PLUS:
	  //il faut lire deux  expressions après un opérateur
	  parse_exp(l,&v1);
	  parse_exp(l,&v2);
	  *v = v1 + v2;
	   break;
	case MULT:
	  //il faut lire deux  expressions après un opérateur
	  parse_exp(l,&v1);
	  parse_exp(l,&v2);
	  *v = v1 * v2;
	   break;
	case DIV:
	  //il faut lire deux  expressions après un opérateur
	  parse_exp(l,&v1);
	  parse_exp(l,&v2);
	  *v = v1/ v2;
	   break;
	case MINUS:
	  //il faut lire deux  expressions après un opérateur
	  parse_exp(l,&v1);
	  parse_exp(l,&v2);
	  *v = v1 - v2;
       	  break;
       default:
                unexpected(current, *v, "exp");              
        }
}

void parse_input(list l) {
        int v;
        /* A CORRIGER: on reconnaît juste une expression (sans '?' devant) */ //corrigé :)
	token current = next(&v);
	while(current != END){
	assert(current == QUEST);
        parse_exp(l, &v);
        append(l, v);
	current = next(&v);
	}// L'affichage est fait dans "append" (cf. commentaires dans "list.h")
}

int main() {
        printf("// Mini-calculator.\n//\n") ;
        printf("// Enter below a sequence of integer computations (using prefix notation).\n");
        printf("// Each computation must start with '?'.\n") ;
        printf("// Type Ctrl-D to quit.\n") ;
        parse_input(empty());
        /* Ligne suivante à garder, pour vérifier qu'on sort proprement */
        printf("// End of Input: Bye !\n") ;
        return 0;
}
