/* Interface of a lexer (for calculators) */

#ifndef _LEXER_H
#define _LEXER_H 1

typedef enum { INT, VAR, QUEST, PLUS, MINUS, MULT, DIV, OPAR, CPAR, END } token;

/* next(v) returns the next token of the input stream.
   *v is only modified when the returned token is INT or VAR
   In this case, *v is the integer read in the stream.
*/ 
extern token next(int *v);

/* display t and its possible attribute v
   if v < 0 then v is considered as irrelevant 
   (it is printed as "...")
*/
extern void display(token t, int v);

/* 1) print an error message "unexpected token"
   displaying t and its possible attribute v 
   with an explanation mesg (possibly empty),
   2) then, stop execution (exit).
 */
extern void unexpected(token t, int v, const char *mesg);



#endif /* !_LEXER_H */
