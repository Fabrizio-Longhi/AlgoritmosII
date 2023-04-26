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
    bool b= false;
    bool aux=true;
    unsigned int max_one= fstring_length(s1);
    unsigned int max_two= fstring_length(s2);

    if (!fstring_eq(s1,s2)){        //si s1 y s2 no son iguales
        if (max_one==max_two){      //s1 s1 y s2 tienen el mismo tamaño
            for (unsigned int i=0; i<max_one && aux; ++i){
                if (s1[i] < s2[i]){                     //si s1[i] es mas chica que s2[i], termina
                    b=true;
                    break;
                }
                else{
                    if (s1[i]!=s2[i]){                  //si s1[i] es igual s2[i] sigue recorriendo
                        aux=false;                      //si s2[i] es mas grande que s1[i] se termina
                    }
                }
            }
        }
        else if (max_one>max_two){
            for (unsigned int i=0; i<=max_two && aux; ++i){
                if (s1[i] < s2[i]){                     //si s1[i] es mas chica que s2[i], termina
                    b=true;
                    break;
                }
                else{
                    if (s1[i]!=s2[i]){                  //si s1[i] es igual s2[i] sigue recorriendo
                        aux=false;                      //si s2[i] es mas grande que s1[i] se termina
                    }
                }

            }
        }
        else{
            for (unsigned int i=0; i<=max_one && aux; ++i){
                if (s1[i] < s2[i]){                     //si s1[i] es mas chica que s2[i], termina
                    b=true;
                    break;
                }
                else{
                    if (s1[i]!=s2[i]){                  //si s1[i] es igual s2[i] sigue recorriendo
                        aux=false;                      //si s2[i] es mas grande que s1[i] se termina
                    }
                }
                if (i==max_one && s1[i]=='\0' && s2[i]!='\0'){  //es necesario cuando hay prefijos
                    b=true;
                }
            }
        }

    }
    else{                           //si s1 y s2 son iguales
        b=true;
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