#include "uhp.h"

void 
slist_init(struct slist *list)
{
        list->head         = NULL;
        list->current      = NULL;
        list->tail         = NULL;
}

void
slist_insert(struct slist *list, void *data)
{
        struct entry *e = entry_new();
        if (e == NULL) {
                perror("Can,t get a new entry");
                return; 
        }
        e->data = data;
        if(list->head == NULL) {
                list->tail = e;
                e->next = NULL;
        } else {
                e->next = list->head;
        }
        list->head = e;
}

void
slist_append(struct slist *list, void *data) {
        struct entry *e = entry_new();
        if (e == NULL) {
                perror("Can,t get a new entry");
                return; 
        }
        e->data = data;
        e->next = NULL;
        if (list->head == NULL) {
                list->head = e;
        } else {
                list->tail->next = NULL;
        }
        list->tail = e;
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
