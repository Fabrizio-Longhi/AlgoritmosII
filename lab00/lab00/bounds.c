#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    bool is_big=true;
    bool is_small=true;
    bool in_arr=false;
    unsigned int where;

    
    for (unsigned int i=0;  i<length; i++){
        if (arr[i]<= value && is_big){            //veo si es mas grande
            is_big=true;
        }
        else{
            is_big=false;
        }
        
        if (arr[i]>value && is_small){          //veo si es mas chico
            is_small=true;
        }
        else{
            is_small=false;
        }

        if(arr[i]==value){
            in_arr=true;                        //veo si esta
            where=i;                            //guardo la posicion
        }
    }

    res.is_upperbound=is_big;
    res.is_lowerbound=is_small;
    res.exists=in_arr;
    res.where=where;
    return res;
}

int main(void) {
    
    int a[ARRAY_SIZE];
    int value;
    bool is_big=true;
    bool is_small=true;

    for (unsigned int i=0; i<ARRAY_SIZE; ++i) {
        printf ("Ingrese valor de la posicion\n");  
        scanf ("%d",&a[i]);
    }

    printf ("De valor para value\n");
    scanf ("%d",&value);
    struct bound_data result = check_bound(value, a,ARRAY_SIZE);

    printf("todos mayores: %d\n", result.is_upperbound); // Imprime 1
    printf("todos menores: %d\n", result.is_lowerbound); // Imprime 0
    printf("existe: %u\n", result.exists);        // Imprime 1
    printf("donde esta: %u\n", result.where);         // Imprime 2

    for (unsigned int i=0; i<ARRAY_SIZE; ++i){          
        if (a[i]<=value && is_big){             //veo si es maximo
            is_big=true;
        }
        else{
            is_big=false;
        }

        if (a[i]>=value && is_small){           //veo si es minimo
            is_small=true;
        }
        else{
            is_small=false;
        }
    }

    
    if (is_small){
        printf ("El minimo es: %d \n",value);
    }
    if (is_big){
        printf ("El maximo es: %d\n", value);
    }
    return EXIT_SUCCESS;
}





