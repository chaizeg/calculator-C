/* Implementation of a calculator in infix notation */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"
#include "list.h" 

/* look a-head */
static token current;
static int att; /* attribute of current */ 

/* prototype */
void parse_exp2(list l, int *res);

/* parsing of token */
void parse_token(token expected) {
        if (current != expected) {
                printf("ERROR: expected token ");
                display(expected, -1);
                printf(" but found ");
                display(current, att);
                printf("\n");
                exit(1);
        }
        if (current != END) {
                current = next(&att);
        }
}

void parse_exp0(list l, int *res){
    int n;
    switch (current){
        case INT:
            *res = att;
            parse_token(INT);
            break;
        case VAR:
            *res = pick(l, att);
            parse_token(VAR);
            break;
        case OPAR:
            parse_token(OPAR);
            parse_exp2(l, res);
            parse_token(CPAR);
            break;
        case MINUS:
            parse_token(MINUS);
            parse_exp0(l, &n);
            *res = -n;
            break;
        default:
            unexpected(current, att, "parse_exp0");
            break;
    }
}

void _parse_exp1(list l, int n, int *res){
    int n0;
    switch (current){
        case MULT:
            parse_token(MULT);
            parse_exp0(l, &n0);
            _parse_exp1(l, n * n0, res);
            break;
        case DIV:
            parse_token(DIV);
            parse_exp0(l, &n0);
            _parse_exp1(l, n / n0, res);
            break;
        case PLUS:case MINUS:case CPAR:case QUEST:
            *res = n;
            break;
        default:
            unexpected(current, att, "parse_exp1");
            break;
    }
}

void parse_exp1(list l, int *res){
    int n;
    switch (current){
        case MINUS:case INT:case VAR: case OPAR:
            parse_exp0(l, &n);
            _parse_exp1(l, n, res);
            break;
        default:
            unexpected(current, att, "parse_exp1");
            break;
    }
}

void _parse_exp2(list l, int n, int *res){
    int n0;
    switch (current){
        case PLUS:
            parse_token(PLUS);
            parse_exp1(l, &n0);
            _parse_exp2(l, n + n0, res);
            break;
        case MINUS:
            parse_token(MINUS);
            parse_exp1(l, &n0);
            _parse_exp2(l, n - n0, res);
            break;
        case CPAR:case QUEST:
            *res = n;
            break;
        default:
            unexpected(current, att, "parse_exp2");
            break;
    }
}

void parse_exp2(list l, int *res){
    int n;
    switch (current){
        case MINUS:case INT:case VAR: case OPAR:
            parse_exp1(l, &n);
            _parse_exp2(l, n, res);
            break;
        default:
            unexpected(current, att, "parse_exp2");
            break;
    }
}

void parse_input(list l, list *res){
    int n;
    switch (current){
        case MINUS:case INT:case VAR:case OPAR:
            parse_exp2(l, &n);
            append(l, n);
            parse_token(QUEST);
            parse_input(l, res);
            break;
        case END:
            *res = l;
            break;
        default:
            unexpected(current, att, "parse_input");
            break;
    }
}

list parse(){
    list res;
    list l = empty();
    parse_input(l, &res);
    return res;
}

int main() {
        printf("// Mini-calculator.\n//\n") ;
        printf("// Enter below a sequence of integer computations (using infix notation).\n");
        printf("// Each computation must end with '?'.\n") ;
        printf("// Type Ctrl-D to quit.\n") ;
        /* A FAIRE */
        current = next(&att); /* init de current */
        list res=empty();
        parse_input(empty(), &res);
        /* Ligne suivante à garder, pour vérifier qu'on sort proprement */
        printf("// End of Input: Bye !\n") ;
        return 0;
}
