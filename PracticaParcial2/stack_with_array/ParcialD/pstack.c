#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node **array;
    priority_t max_priority;
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = malloc (sizeof (struct s_node));
    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->next = node;
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    unsigned int size_aux = 0;
    struct s_node *count = NULL;
    for (unsigned int i = 0 ; i <= s->max_priority ; ++i){
        count = s->array[i];
        while (count != NULL){
            ++size_aux;
            count = count->next;
        }
    }

    return s->size == size_aux;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s = malloc (sizeof (struct s_pstack));
    s->size = 0;
    s->max_priority = max_priority;
    s->array = calloc (s->max_priority+1, sizeof (struct s_node*));

    for (unsigned int i = 0 ; i <=s->max_priority ; ++i){
        s->array[i] = NULL;
    }

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s) && priority <= s->max_priority);
    struct s_node *new_node = create_node (e);

    if (s->array[priority] == NULL){
        s->array[priority] = new_node;
    }else{
        struct s_node *aux = s->array[priority];
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new_node;
    }
    ++s->size;

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {    
    assert(invrep(s));
    
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    unsigned int i = s->size-1;
    while (s->array[i] == NULL){
        ++i;
    }

    return s->array[i]->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    unsigned int i = s->size-1;
    while (s->array[i] == NULL){
        ++i;
    }

    return i;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));


    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    unsigned int i = s->size-1;
    struct s_node *kill = NULL;
    while (s->array[i] == NULL){
        ++i;
    }

    
    kill = s->array[i];
    s->array[i] = kill->next;
    kill = destroy_node (kill);

    --s->size;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *kill = NULL;
    for (unsigned int i = 0 ; i<=s->max_priority ; ++i){
        while (s->array[i] != NULL){
            kill = s->array[i];
            s->array[i] = kill->next;
            kill = destroy_node (kill);
        }
    }
    free (s->array);
    free(s);
    s = NULL;
    return s;
}
