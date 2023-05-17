#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};


bool invrep (stack s){
    
    return s->capacity>=s->size && s!=NULL; 
}

stack stack_empty (){
    stack s = malloc (sizeof(struct _s_stack));         //Reserve memory for stack
    s->elems = malloc (sizeof(stack_elem));             //Reserve memory for array
    s->size = 0;
    s->capacity = 0;

    return s;
}

stack stack_push(stack s, stack_elem e){
    unsigned int cap_aux=s->capacity;

    if (s->size==0){                                    //if size is equal a zero
        cap_aux=1;                                      //My new capacity es one, I need this capacity
    }
    else{
        if (s->size == s->capacity){                    //if si size is equal a the capacity
            cap_aux= s->capacity*2;                     //Double my capacity
            s->elems= realloc(s->elems,sizeof (stack_elem) * cap_aux);  
        }
    }
    
    s->capacity=cap_aux;            //Assign my new capacity
    s->elems[s->size]=e;            //Insert my elem
   
    ++s->size;

    return s;
}


    
stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    --s->size;
    
    return s;
}

unsigned int stack_size(stack s){

    return s->size;
}


stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));

    return s->elems[s->size-1];
}



bool stack_is_empty(stack s){

    return s->size == 0;
}


stack_elem *stack_to_array(stack s){
    stack_elem *array = calloc (s->size,sizeof(stack_elem));    //Reserve memory for my array

    for (unsigned int i=0; i<s->size; ++i){
        array[i] = s->elems[i];
    }

    return array;
}



stack stack_destroy(stack s){
    free(s->elems);
    free(s);
    return s;
}