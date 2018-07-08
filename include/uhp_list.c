#include <stdlib.h>

#include "uhp.h"

void 
slist_init(struct slist *list, int size)
{
        list->head         = NULL;
        list->current      = NULL;
        list->tail         = NULL;
        /* length of the list */
        list->len          = 0;
}

void
slist_insert(struct slist *list, void *data)
{
        struct entry *e = entry_new();
        if (e == NULL) {
                perror("Can,t get a new entry");
		exit(-1);
        }
        e->data = data;
        if(list->head == NULL) {
                list->tail = e;
                e->next = NULL;
        } else {
                e->next = list->head;
        }
        list->head = e;
        list->len++;
}

void *
slist_pop(struct slist *list)
{
        void *data = NULL;
        list->current = list->head;

        if (list->current == NULL) {
                data = NULL;
        } else if (list->current == list->tail) {
                list->head = list->tail = NULL;
                data = list->current->data;
                free(list->current);
                list->len--;
        } else {
                list->head = list->head->next;
                data = list->current->data;
                free(list->current);
                list->len--;
        }
        
        return data;
}


int
slist_is_empty(struct slist *list)
{
        return((list->len == 0)?0:1); 
}

void
slist_print(struct slist *list, void(*entry_print)(void *)) 
{
        list->current = list->head;
        while (list->current != NULL) {
                entry_print(list->current->data);
                list->current = list->current->next;
        }
}

struct entry *
entry_new()
{
        struct entry *e = malloc(sizeof(struct entry));
        if (e == NULL){
                perror("Malloc failed");        
                return NULL;
        }
        return e;
}


struct entry *
entry_get(struct slist *list, int(*entry_cmp)(void *, void *), void *data)
{
        list->current = list->head;

        while (list->current != NULL) {
                if (entry_cmp(list->current->data,data) == 0)
                        return list->current;

                list->current = list->current->next;        
        }

        return NULL;
}

int
entry_find(struct slist *list, int(*entry_cmp)(void *, void *), void *data)
{
        return ((entry_get(list, entry_cmp, data) == NULL?1:0));
}

