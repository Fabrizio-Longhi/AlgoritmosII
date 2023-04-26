/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int array_from_file(int array[], unsigned int max_size,const char *filepath) {
    unsigned int e;                         //voy a usar para guardar los elementos
    int scans_r;
    FILE * fp;                              //puntero a archivo

    fp=fopen (filepath,"r");                //abre la ruta filepath
    fscanf(fp,"%u",&max_size);
    if (fp ==NULL){                         //si no logra abrirlo
        printf ("Problem opening file\n");
        exit(0);
    }
    else{
        for (unsigned int i=0; i<max_size; ++i){  
            scans_r = fscanf (fp, "%u,",&e);    //almaceno el valor en e

            if (scans_r != EOF){
                array[i]=e;                     //guardo a e en el array
            }
            else{
                printf ("Invalid array\n");
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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
