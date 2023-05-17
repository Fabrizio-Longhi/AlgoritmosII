#include <stdlib.h>
#include <assert.h>
#include "stack.h"


struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};


stack stack_empty(){
    stack s=NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack new = malloc (sizeof(struct _s_stack)); //reserve memory for my node
    new->elem=e;
    new->next=NULL;

    if (s!=NULL){                   //if stack is not empty
        new->next=s;
        s=new;
    }
    else{
        s=new;
    }

    return s;
}


stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    stack kill=s;
    s=kill->next;
    free(kill);

    return s;
}


unsigned int stack_size(stack s){
    unsigned int size=0;
    stack aux=s;

    while (aux!=NULL){
        ++size;
        aux=aux->next;
    }

    return size;
}


stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    return s==NULL;
}


stack_elem *stack_to_array(stack s){
    stack aux= s;
    unsigned int size=stack_size(s); 
    stack_elem *array = calloc (size,sizeof(stack_elem));

    for (int i=size-1; i>=0;--i){
        array[i]=aux->elem;
        aux=aux->next;
    }

    return array;
}



stack stack_destroy(stack s){
    stack kill;
    while (s!=NULL){
        kill=s;
        s=kill->next;
        free(kill);
    }
    free(s);
    
    return s;
}