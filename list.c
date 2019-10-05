/* An implementation of "list.h" interface
   based on resizeable arrays
   (ensures a constant amortized cost)
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct _list {int next; int size; int *elements;};

static void *protect(void *p){
        if (p==NULL) {
                printf("ERROR: unexpected null pointer. No memory left ?\n");
                exit(1);
        }
        return p;
}

list empty() {
        list res=protect(malloc(sizeof(struct _list)));
        res->next=0;
        res->size=2;
        res->elements=protect(malloc(res->size*sizeof(int)));
        return res;
}

int length(list l){
        assert (l != NULL);
        return l->next;
}

void append(list l, int v){
        int n;
        assert (l != NULL);
        n=l->next++;
        if (n >= l->size) {
                l->size *= 2;
                l->elements = protect(realloc(l->elements, l->size*sizeof(int)));
        }
        assert (n < l->size);
        l->elements[n] = v;
        printf("#%d = %d\n", n+1, v);
}

int pick(list l, int i){
        assert (l != NULL);
        if (i < 1 || i > l->next) {
                printf("ERROR: #%d unassigned\n", i);
                exit(1);
        }
        return l->elements[i-1];
}

void destruct(list *l){
        list x;
        assert (l != NULL);
        x=*l;
        *l=NULL;
        if (x == NULL) 
                return;
        free(x->elements);
        free(x);
}
