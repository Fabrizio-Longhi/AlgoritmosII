#include <stdio.h>
#include "stack.h"
#include <stdbool.h>

int main (){
    stack s= stack_empty();
    stack_elem elem1=4;
    stack_elem elem2=8;
    stack_elem elem3=12;
    stack_elem elem4=16;

    bool b= stack_is_empty(s);
    printf ("Is empty? %u\n",b);

    s=stack_push(s,elem1);
    s=stack_push(s,elem2);
    s=stack_push(s,elem3);
    s=stack_push(s,elem4);
    
    bool b_aux= stack_is_empty(s);
    printf ("Is empty? %u\n",b_aux);

    unsigned int size= stack_size(s);
    printf ("This is the lenght of array: %d\n",size);

    stack_elem first= stack_top(s);
    printf ("The top is: %d\n",first);

    stack_elem *array = stack_to_array(s);

    printf ("This is the array: \n");
    printf ("[");
    for (unsigned int i=0; i<size; ++i){
        printf ("%d,",array[i]);
    }
    printf ("]\n");

    s= stack_pop(s);
    s= stack_pop(s);
    s= stack_pop(s);
    s= stack_pop(s);

    bool b_aux1= stack_is_empty(s);
    printf ("Is empty? %u\n",b_aux1);

    s=stack_destroy(s);


    return 0;
}


//¿Funciona bien stack_pop() para pilas de tamaño 1?
//Funciona bien, la pila queda vacia nomas

//Si la pila queda vacía, ¿puedo volver a insertar elementos?
//Si, se puede volver a insertar


//La función stack_to_array() devuelve NULL para una pila vacía? ¿Devuelve los elementos en el orden correcto?
//No, devuelve un arreglo vacio, no devuelve los elementos en orden.