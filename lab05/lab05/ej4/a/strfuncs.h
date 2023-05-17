#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdio.h>


//Return the lenght of the str
size_t string_length(const char *str);


//Return a new str in the heap which are obtained by taking
//characters in str that are other than the character c.
char *string_filter(const char *str, char c);

#endif