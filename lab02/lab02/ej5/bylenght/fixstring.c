#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


//unsigned int fstring_length(fixstring s);
unsigned int fstring_length(fixstring s) {
    unsigned int size=0;
    unsigned int i=0;

    while (s[i]!='\0'){
        ++size;
        ++i;
    }
    return size;
}


//indica si las cadenas s1 y s2 son iguales
bool fstring_eq(fixstring s1, fixstring s2) {
    bool b=true;
    unsigned int i=0;

    if (fstring_length(s1) == fstring_length(s2)){
        
        while (s1[i]!='\0' && b){
        if (s1[i]==s2[i]){
            ++i;
        }
        else{
            b=false;
        }
    }
    }
    else{
        b=false;
    }

    return b;   
}


//indica si la cadena guardada en s1 es menor o igual que la guardada en s2 en el sentido del orden alfabético
bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool b;
    unsigned int lenght_1= fstring_length(s1);
    unsigned int lenght_2= fstring_length(s2);

    assert(lenght_1 <= FIXSTRING_MAX && lenght_1 <= FIXSTRING_MAX);
    if (lenght_1<=lenght_2){
        b=true;
    }
    else{
        b=false;
    }

    return b;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

//Debe intercambiar los contenidos de las cadenas s1 y s2
void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux_s2;
    fstring_set(aux_s2,s2) ;

    fstring_set(s2,s1);
    fstring_set(s1,aux_s2);
}


