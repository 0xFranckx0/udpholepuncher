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
        /* size of the data should be assign with sizeof operator */
        list->size         = size;
}

void
slist_insert(struct slist *list, void *data)
{
        struct entry *e = entry_new();
        if (e == NULL) {
                perror("Can,t get a new entry");
                goto error;
        }
        e->data = malloc(sizeof(list->size));
        if(e->data == NULL) {
                perror("Malloc failed");
                goto error;
        }
        memcpy(e->data, data, list->size);
        if(list->head == NULL) {
                list->tail = e;
                e->next = NULL;
        } else {
                e->next = list->head;
        }
        list->head = e;
        list->len++;
        return;
error:
        if (e->data != NULL) 
                free(e->data);

        entry_delete(list, NULL, e);        
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

/*

Function entry_delete
  - Params: 
        - struct slist *list: the list in which you want to delete an item
        - data_free: A function to free the data inside the entry. Can be NULL
                     if you free the data by yourself.
        - struct entry *entry: the entry to delete and free.             

*/
void
entry_delete(struct slist *list, void(*data_free)(void *), struct entry *entry)
{
        if (entry == list->head) {
                if (list->head->next == NULL) {
                        list->head = list->tail = NULL;
                } else {
                        list->head = list->head->next;
                }
        } else {
                list->current = list->head;
                while ( list->current != NULL && list->current->next != entry){
                        list->current = list->current->next;
                }
                if (list->current != NULL)
                        list->current->next = entry->next;
        }
        if (data_free != NULL)
                data_free(entry->data);
        if (entry != NULL)
                free(entry);
        list->len--;
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

