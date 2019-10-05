# Makefile pour compiler les sources Flex/Bison de la calculette.
#
# Pour installer Flex et Bison sous Ubuntu:
#  sudo apt-get install flex libfl-dev bison

calc: lex.yy.c calc.tab.c list.c
	gcc -o calc calc.tab.c lex.yy.c list.c -ll
calc.tab.h calc.tab.c: calc.y
	bison -Werror -d calc.y
lex.yy.c: calc.tab.h calc.lex
	flex calc.lex
clean:
	rm -f calc.tab.* lex.yy.c *~ calc

