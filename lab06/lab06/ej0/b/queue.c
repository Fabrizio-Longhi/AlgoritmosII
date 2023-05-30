#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    unsigned int size;
    struct s_node *last;        //last node
    struct s_node *first;       //first node
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q = malloc (sizeof(struct s_queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;

    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->first==NULL) {                       //if queue  is empty
        q->first = new_node;
        q->last=new_node;
    } else {                                    //is not empty
        q->last->next=new_node;
        q->last=new_node;
    }
    ++q->size;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));

    return q->size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    --q->size;
    assert(invrep(q));
    return q;

}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}




queue queue_disscard(queue q, unsigned int n){
    struct s_node *kill = NULL;
    struct s_node *aux = NULL;


    if (n == 0){                              //remove first node
        q = queue_dequeue(q);
        return q;
    } else if (n == q->size-1){               //remove last node
        aux = q->first;
        while (aux->next->next != NULL){
            aux = aux->next;
        }
        kill = aux->next;
        q->last = aux;
        aux->next = NULL;

        kill = destroy_node(kill);
    }
    else{                                   //remove the node between of extrems
        kill = q->first;
        for (unsigned int i = 0; i <= n; ++i){
            if(i == n){
                aux->next = kill->next;
                kill = destroy_node(kill);
            }
            else{
                aux = kill;
                kill = kill->next;
            }
        }
    
    }

    --q->size;

    return q;
}