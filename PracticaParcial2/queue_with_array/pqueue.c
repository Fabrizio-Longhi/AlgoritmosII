#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    priority_t min_priority;
    struct s_node **array;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node = malloc (sizeof(struct s_node));
    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->next = NULL;
    free (node);
    node = NULL;

    return node;
}


static bool invrep(pqueue q) {
    unsigned int size = 0;
    struct s_node *count = NULL;

    for (unsigned int i = 0 ; i <= q->min_priority ; ++i){
        count = q->array[i];
        while (count != NULL){
            ++size;
            count = count->next;
        }
    }
    return q->size == size;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = malloc (sizeof (struct s_pqueue));
    q->min_priority = min_priority;
    q->size = 0;
    q->array = calloc (min_priority+1,sizeof(struct s_node *));

    for (unsigned int i = 0;i <=q->min_priority ; ++i){
        q->array[i] = NULL;
    }
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    
    struct s_node *new_node = create_node (e);
    if (q->array[priority] == NULL){
        q->array[priority] = new_node;
    }
    else{
        struct s_node * aux = q->array[priority];
        while (aux->next != NULL){
            aux = aux->next;
        } 
        aux->next = new_node;
    }

    ++q->size;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));

    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;

    while (q->array[i] == NULL) {
        ++i;
    }

    return q->array[i]->elem;
}

priority_t pqueue_peek_priority(pqueue q) { 
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;
    
    while (q->array[i] == NULL){
        ++i;
    }

    return i;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));

    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;
    struct s_node *kill = NULL;

    while (q->array[i] == NULL){
        ++i;
    }

    kill = q->array[i];
    q->array[i] = kill->next;
    kill = destroy_node (kill);

    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *kill = NULL;

    for (unsigned int i = 0; i<= q->min_priority; ++i){
        while (q->array[i] != NULL){
            kill = q->array[i];
            q->array[i] = kill->next;
            kill = destroy_node (kill);
            kill = NULL;
        }
    } 
    free (q->array);
    free (q);
    q = NULL;

    return q;
}