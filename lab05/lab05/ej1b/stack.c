#include <stdlib.h>
#include <assert.h>
#include "stack.h"


struct s_node{              //struct node
    stack_elem elem;
    struct s_node *next;
};

struct _s_stack {           //struct stack
    unsigned int size;
    struct s_node * top;  
};

bool invrep(stack s){       // check if the number of nodes is equal to the size
    bool res=true;
    unsigned int size=0;
    node aux=s->top;

    while (aux!=NULL){
        ++size;
        aux=aux->next;
    }

    res= size ==s->size;
    return res;
}

node destroy_node (node n){
    free(n);
    n=NULL;
    return n; 
}

stack stack_empty(){
    stack s= malloc (sizeof (struct _s_stack)); //reserve memory for stacj  
    s -> size = 0;
    s -> top = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    node new = malloc (sizeof(struct s_node));  //create node
    new->elem=e;
    new->next=NULL;

    if (s!=NULL){           //if stack isnt empty
        new->next=s->top;
        s->top=new;
    }
    else{                   //if stack is empty
        s->top=new;
    }
    ++s->size;              //increment the size
    assert(invrep(s));
    return s;
}


stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));
    node kill=s->top;       
    s->top=kill->next;      //Now the first node of my stack is the second node
    kill=destroy_node(kill);

    --s->size;
    assert(invrep(s));
    return s;
}


unsigned int stack_size(stack s){

    return s->size;
}


stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));
    return s->top->elem;
}

bool stack_is_empty(stack s){
    assert(invrep(s));
    return s->size==0;
}


stack_elem *stack_to_array(stack s){
    stack_elem *array = calloc (s->size,sizeof(stack_elem));    //reserve memory for my array
    node aux= s->top;

    for (int i=s->size-1; i>=0;--i){        //insert from right to left
        array[i]=aux->elem;
        aux=aux->next;
    }

    return array;
}



stack stack_destroy(stack s){
    node kill;
    while (s->top!=NULL){
        kill=s->top;
        s->top=kill->next;
        kill=destroy_node(kill);        //remove all nodes
    }
    free(s->top);
    free(s);
    return s;
}