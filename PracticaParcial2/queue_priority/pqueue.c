#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;       
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;    
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = malloc (sizeof (struct s_node));

    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next=NULL;
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool b_one = false;
    unsigned int size_aux = 0;
    struct s_node * count_size = q->front;
    while (count_size != NULL){             //count the size of nodes
        ++size_aux;
        count_size = count_size->next;
    }

    if (q->front == NULL){                  // if pqueue is empty, the priority is correct
        b_one=true;
    }
    else{                                   //check the priority
        struct s_node * aux = q->front;
        if (aux->next == NULL){             //if pqueue has one element, priority is correct
            b_one = true;
        }
        else{
            while (aux->next != NULL){
                b_one = aux->priority <= aux->next->priority;
                aux=aux->next;
            }
        }
    }

    return b_one  && size_aux == q->size;
}

pqueue pqueue_empty(void) {
    pqueue q = malloc (sizeof (struct s_pqueue));
    q->front = NULL;
    q->size = 0;
    assert (invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
   
    if (q->front==NULL){                       //pqueue is empty
        q->front = new_node;
    }           
    else{                                                           //pqueue isnt empty
        struct s_node *post = q->front;                             //pointer to next
        struct s_node *pre = NULL;                                  //pointer to prev
        while (post->next!= NULL && post->priority <= new_node->priority){
            pre=post;
            post = post->next;
        }
        if (q->front->priority > new_node->priority){               //insert in first place
            new_node->next = post;
            q->front = new_node;
        }
        else if (post->priority > new_node->priority){            //insert beetwen of extrems
            new_node->next = post;
            pre ->next = new_node;
        }else if (post->priority <= new_node->priority){         // insert last
            post->next = new_node;

        }

    
    }
    ++q->size;
    return q;
}

bool pqueue_is_empty(pqueue q) {

    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert (!pqueue_is_empty(q));
    
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(!pqueue_is_empty(q));

    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));

    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q));
    struct s_node *kill = q->front;
    q->front = kill->next;
    kill= destroy_node(kill);

    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node* kill = NULL;

    while (q->front!= NULL){
        kill = q->front;
        q->front = kill->next;
        kill = destroy_node(kill);
    }
    free(q);
    q=NULL;
    assert(q == NULL);
    return q;
}