#include <stdio.h>
#include "lexer.h"

int main() {
        int val;
        token current;
        printf("// Console for lexical analysis.\n//\n") ;
        printf("// Enter below a sequence of tokens.\n");
        printf("// Type Ctrl-D to quit.\n") ;
        do {
                current = next(&val);
                printf("// see token ");
                display(current, val);
                printf("\n");
        } while (current != END);
        return 0;
}
