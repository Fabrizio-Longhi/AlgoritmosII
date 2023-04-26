#include <stdio.h>
#include "array_helpers.h"
#include <stdlib.h>


unsigned int array_from_file(int array[], unsigned int max_size,const char *filepath) {
    FILE * fp;                              //puntero a archivo
    int e;
    int scan_r;

    fp=fopen (filepath,"r");                //abre la ruta filepath
    fscanf(fp,"%u",&max_size);
    if (fp ==NULL){                         //si no logra abrirlo
        printf ("Problem opening file\n");
        exit(0);
    }
    else{
        for (unsigned int i=0; i<max_size; ++i){    
            scan_r= fscanf (fp, "%d,",&e);    //almaceno el valor en array

            if(scan_r != EOF){
                array[i]=e;
            }
            else{
                printf ("Invalid Array\n");
                exit(1);
            }
        }
    }
    fclose (fp);
    return max_size;
}

void array_dump(int a[], unsigned int length) {
    printf ("%d\n",length);                 //printeo la la longtitud
    printf ("[");
    for (unsigned int i=0; i< length; ++i){
        printf("%d,",a[i]);                 //printeo cada valor
    }
    printf ("]\n");
}
