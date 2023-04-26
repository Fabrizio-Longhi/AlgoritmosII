#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x>=0){
        *y=x;
    }
    else{
        *y=-x;
    }
}

int main(void) {
    int a=0, res=0;
    a=-10;  
    int *p= &res;    //saco la direccion de memoria de mi variable de salida

    absolute (a,p);  //mando mi "a"(variable a aplicar abs), y la direcciòn de mi variable q va almacenar el abs
    res= *p;         //guardo en res, el absoluto de "a"
    printf ("Valor absoluto es : %d \n",res);

    return EXIT_SUCCESS;
}

// "y" es una variable out

//En c existen las variables in, in/out y out.