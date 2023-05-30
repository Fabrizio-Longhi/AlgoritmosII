#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

struct _s_string {
    char *content;
    unsigned int length;
};

string string_create(const char *word) {
    string str = NULL;
    str =  malloc (sizeof (struct _s_string));
    str->length = strlen(word);
    str->content = calloc(str->length+1, sizeof(char));
    str->content = strncpy(str->content, word, str->length + 1);
    return (str);
}

unsigned int string_length(string str) {
    return (str->length);
}

bool string_less(const string str1, const string str2) {
    bool b = false;
    bool aux = true;
    unsigned int i = 0; 
    bool size_aux = str1->length > str2->length;
    if (string_eq(str1,str2)){
        if (size_aux){          //if str1 is big and str2 is small
            while (str2->content[i] != '\0' && !b && aux){
                if (str1->content[i] < str2->content[i]){
                    b=true;
                }
                else if (str1->content[i] > str2->content[i]){
                    aux=false;
                }
                else{
                    ++i;
                }
            }
        }
        else{                   //if str2 is big and str1 is small
            while (str1->content[i] != '\0' && !b && aux){
                if (str1->content[i] <   str2->content[i]){
                    b=true;
                }
                else if (str1->content[i] > str2->content[i]){
                    aux=false;
                }
                else{
                    ++i;
                }
            }
        }
    }
    
    return b;
}

bool string_eq(const string str1, const string str2) {
    int cmp = strcmp(str1->content, str2->content);
    return (cmp == 0);
}

string string_clone(const string str) {
    return (string_create(str->content));
}

string string_destroy(string str) {
    free(str->content);
    free(str);
    str = NULL;
    return (str);
}

void string_dump(string str, FILE *file) {
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str) {
    return (str->content);
}
