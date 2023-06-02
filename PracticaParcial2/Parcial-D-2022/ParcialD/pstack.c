#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    priority_t max_priority;
    struct s_node **array;
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

    node->next =NULL;
    free (node);
    node = NULL;

    return node;
}


static bool invrep(pstack s) {
    unsigned int size_aux = 0;
    struct s_node *aux = NULL;

    for (unsigned int i = 0; i <= s->max_priority; ++i){
        aux = s->array[i];
        while (aux != NULL){
            ++size_aux;
            aux = aux->next;
        }
    }
    return size_aux == s->size;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s = malloc (sizeof (struct s_pstack));

    s->size = 0;
    s->max_priority = max_priority;
    s->array = calloc (s->max_priority+1, sizeof (struct s_node*));

    for (unsigned int i = 0 ; i <= s->max_priority; ++i){
        s->array[i] = NULL;
    }

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));

    struct s_node * new_node = create_node (e);

    if (s->array[priority] == NULL){        //if stack is empty
        s->array[priority] = new_node;
    }
    else{
        new_node->next = s->array[priority];
        s->array[priority] = new_node;
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

    unsigned int index = s->max_priority;

    while (s->array[index] == NULL){
        --index;
    }

    return s->array[index]->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    unsigned int index = s->max_priority;

    while (s->array[index] == NULL){
        --index;
    }

    return index;

}

size_t pstack_size(pstack s) {
    assert(invrep(s));

    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    unsigned int index = s->max_priority;
    struct s_node *kill = NULL;

    while (s->array[index] == NULL){
        --index;
    }

    kill = s->array[index];
    s->array[index] = kill->next;
    kill= destroy_node (kill);
    
    --s->size;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));

    struct s_node *kill = NULL;

    for (unsigned int i = 0 ; i <= s->max_priority; i++){
        while (s->array[i] != NULL){
            kill = s->array[i];
            s->array[i] = kill->next;
            kill = destroy_node (kill);
        }
    }
    free (s->array);
    free (s);
    s = NULL;
    return s;
}
