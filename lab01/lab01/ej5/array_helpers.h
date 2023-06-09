#ifndef EJ5_ARR_HELPERS
#define EJ5_ARR_HELPERS
#include "mybool.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath); 

void array_dump(int a[], unsigned int length);

mybool array_is_sorted(int a[], unsigned int length);
#endif