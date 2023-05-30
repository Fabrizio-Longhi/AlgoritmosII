#include <stdio.h>
#include "string.h"
#include <stdbool.h>

int main (){
    string ejem1 = string_create ("Boca");
    string ejem2 = string_create ("River");

    bool b = string_eq (ejem1,ejem2);
    if (b){
        printf ("Son los mismos strings \n");
    }
    else{
        printf ("No son los mismos strings \n");
    }

    bool b_aux = string_less (ejem1,ejem2);
    if (b_aux){
        printf ("El primer string es mas chico\n");
    }
    else{
        printf ("EL primer string no es mas chico \n");
    }

    ejem1 = string_destroy (ejem1);
    ejem2 = string_destroy (ejem2);

    return 0;
}