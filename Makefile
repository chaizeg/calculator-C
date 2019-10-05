##########
# MAKEFILE FOURNI
#
# En principe: inutile de le modifier !

GCC := gcc -g -Wall -Werror
EXE := debug_lexer pcalc calc

.PHONY: exe execlean

exe: $(EXE)

# executables
debug_lexer: debug_lexer.o lexer.o
	$(GCC) $^ -o $@

pcalc: pcalc.o lexer.o list.o
	$(GCC) $^ -o $@

calc: calc.o lexer.o list.o
	$(GCC) $^ -o $@

# dependencies
list.o: list.c list.h
lexer.o: lexer.c lexer.h
debug_lexer.o: debug_lexer.c lexer.h
pcalc.o: pcalc.c lexer.h list.h
calc.o: calc.c lexer.h list.h

# modular compilation
%.o: %.c
	$(GCC) -c $< -o $@

# cleaning
execlean:
	$(RM) $(EXE) *.o *~
