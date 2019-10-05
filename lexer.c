/* Implementation of "lexer.h" */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"

/* NB: allocation below requires that END is the last token 
   TAKE CARE to synchronize token_name with token type of lexer.h
*/
static const char* token_name[END+1] = {
        "<INT>",
        "#",
        "?",
        "+",
        "-",
        "*",
        "/",
	"(",
	")",
        "<END>"
};

void display(token t, int v) {
        printf("%s", token_name[t]);
        switch (t) {
        case INT:case VAR:
                if (v >= 0) {
                        printf("%d",v);
                } else {
                        printf("...\n");
                }        
        default:
	     break;
                
        }                
}

void unexpected(token t, int v, const char *mesg) {
        printf("ERROR: unexpected token ");
        display(t, v);
        if (mesg[0] != 0) {
                printf(" in %s", mesg);
        }
        printf("\n");
        exit(1);
}


static int isDigit(char c) {
        return '0' <= c && c <= '9';
}

static int digit(char c) {
        assert(isDigit(c));
        return c - '0';
}

static char current;

static void update_current() {
        current = fgetc(stdin);
}

static void parse_int(int *v) {
     int res=0;
        if (! isDigit(current)) {
                printf("LEXICAL ERROR: unexpected character '%c'\n", current);
                exit(1);
        }
	do{	  
		res = res *(10) + digit(current) ;
	        update_current();
        }while(isDigit(current));

        *v = res;
}

/* Boolean variable indicating whether "current" has been initialized or not.
   NB: this variable is only used in "next".
 */ 
static int init = 0;

token next(int *v) {
        if (! init) {
	  // phase d'initialisation
                update_current();
                init = 1;
        }
        for ( ; ; ) { 
                switch (current) {
                case ' ': case '\t': case '\n':
                        update_current();
			break;
                        
                case '+': 
		     update_current();
		  return PLUS;
		  
		case '-': 
		     update_current();
		  return MINUS;
		  
		case '*':
		     update_current();
		  return MULT;
		  
		case '/': 
		     update_current();
		  return DIV;
		  
                case EOF: 
                  return END;
		  
		case '?':
		     update_current();
		  return QUEST;
		  
		  //on traite en dernier les deux cas de INT et VAR
		case '#':
		     update_current();
		  parse_int(v);
		  return VAR;
		  //cas des parenthèses: rajoutées pour le TP2
		case '(':
		  update_current();
		  return OPAR;
		case ')':
		  update_current();
		  return CPAR;
                default:
                  parse_int(v);   
                  return INT;
		};}       
}
