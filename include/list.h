#ifndef LIST_H
#define LIST_H

struct entry{
        void *data;
        struct entry *next;
};

struct slist{
        struct entry *head;
        struct entry *current;
        struct entry *tail;
        int len;
        int size;
};

/* uhp_list.c */
void             slist_init(struct slist *, int);
void             slist_insert(struct slist *, void *);
void             slist_append(struct slist *, void *);
void            *slist_pop(struct slist *);
int              slist_is_empty(struct slist *);
void             slist_print(struct slist *, void(*)(void *)); 
struct entry    *entry_new();
void             entry_delete(struct slist *, void(*)(void *), struct entry *);
struct entry    *entry_get(struct slist *, int(*)(void *, void *), void *);

#endif /* LIST_H */
