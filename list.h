/* An abstract datatype for list of integers.
*/

#ifndef _LIST_H
#define _LIST_H 1

typedef struct _list *list;

/* Return a new empty list */
extern list empty();

/* Return the number of elements in list l */
extern int length(list l);

/* Append a new integer v at the end of list l. 
   This function also prints the results of our tiny calculators.

   NB: ce dernier choix (peu réaliste pour une bibliothèque de listes) 
   a l'intérêt de simplifier et rapprocher le code de nos trois implémentations.
*/
extern void append(list l, int v);

/* Pick the i-th element of l. 
   i must be in 1..length(l)
*/
extern int pick(list l, int i);

/* Destruct list l and assigns l to NULL */
extern void destruct(list *l);

#endif
