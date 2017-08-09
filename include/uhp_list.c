#include <stdlib.h>

#include "uhp.h"

void 
slist_init(struct slist *list, int size)
{
        list->head         = NULL;
        list->current      = NULL;
        list->tail         = NULL;
        list->len          = 0;
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
        struct entry *entry = list->head;

        if (entry == NULL) {
                data = NULL;
        } else if (entry == list->tail) {
                list->head = list->tail = NULL;
                data = entry->data;
                free(entry);
        } else {
                list->head = list->head->next;
                data = entry->data;
                free(entry);
        }
        
        return data;
}

int
slist_is_empty(struct slist *list)
{
        if (list->len == 0) {
                return 0;
        } else {
                return 1;
        }
}

void
slist_print(struct slist *list, void(*entry_print)(void *)) 
{
        struct entry *current = list->head;
        while (current != NULL) {
                entry_print(current->data);
                current = current->next;
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
        struct entry *tmp;

        if (entry == list->head) {
                if (list->head->next == NULL) {
                        list->head = list->tail = NULL;
                } else {
                        list->head = list->head->next;
                }
        } else {
                tmp = list->head;
                while ( tmp != NULL && tmp->next != entry){
                        tmp = tmp->next;
                }
                if (tmp != NULL)
                        tmp->next = entry->next;
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
        struct entry *entry = list->head;

        while (entry != NULL) {
                if (entry_cmp(entry->data,data) == 0)
                        return entry;

                entry = entry->next;        
        }

        return NULL;
}

int
entry_find(struct slist *list, int(*entry_cmp)(void *, void *), void *data)
{
        list->current = list->head;

        while (list->current != NULL) {
                if (entry_cmp(list->current->data,data) == 0)
                        return 0;

                list->current = list->current->next;        
        }

        return 1;
}

