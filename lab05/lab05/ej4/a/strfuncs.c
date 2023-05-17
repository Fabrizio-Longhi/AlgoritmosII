#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str){
    size_t size=0;
    unsigned int i=0;

    while (str[i]!='\0'){   //iterate to the end 
        ++size;
        ++i;
    }
    
    return size;
}


char *string_filter(const char *str, char c){
    size_t size=string_length(str);
    char * filter = malloc (sizeof(char)*size);     //reserve memory for filter array
    unsigned int index=0;       
    unsigned int iter=0;        

    while (str[iter]!='\0'){        //iterate to the end
        if (str[iter]!=c){              //if my char isnt equal a c
            filter[index]=str[iter];
            ++index;
        }
        ++iter;
    }
    filter[index]='\0';             //my last char is '\0'
    

    return filter;
}