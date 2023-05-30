#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = malloc (sizeof (struct s_node));

    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);

    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool inv = true;
    unsigned int size_aux = 0;
    struct s_node *count_size = s->front;
    while (count_size != NULL){
        ++size_aux;
        count_size =count_size->next;
    }

    if (s->front != NULL){
        struct s_node *aux= s->front;
        if (aux->next == NULL){
            inv = true;
        }else{
            while (aux->next != NULL && inv){
                inv = aux->priority >= aux->next->priority;
                aux = aux->next;
            }
        }
    }
    return size_aux == s->size && inv;
}

pstack pstack_empty(void) {
    pstack s = malloc (sizeof (struct s_pstack));
    s->front = NULL;
    s->size = 0;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);

    if (s->front == NULL){              // if pstack is empty
        s->front = new_node;
    }
    else{                               // if pstack isnt empty
        struct s_node *post = s->front;             //pointer to next
        struct s_node *pre = NULL;                  //pointer to prev
        while (post->next != NULL && new_node->priority <= post->priority){
            pre = post;
            post = post->next;
        }
        if (s->front->priority <= new_node->priority){      //insert in first place
            new_node->next = s->front;
            s->front = new_node;
        }
        else if (new_node->priority >= post->priority){     //insert beetwen of extrems
            new_node->next = post;
            pre->next = new_node;
        }else{                                              //insert a last
            post->next = new_node;
        }
     }
     ++ s->size;
    return s;
}

bool pstack_is_empty(pstack s) {

    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(!pstack_is_empty(s));

    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s));

    return s->front->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));

    return s->size;
}

pstack pstack_pop(pstack s) {
    struct s_node *kill = s->front;
    s->front = kill->next;
    kill = destroy_node (kill);
    --s->size;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *kill;

    while (s->front != NULL){
        kill = s->front;
        s->front = kill->next;
        kill = destroy_node (kill);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}