#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x>=0){
        y=x;
    }
    else{
        y=-x;
    }
}

int main(void) {
    int a=0, res=0;

    a=-10;
    absolute(a,res);
    printf ("Valor de absoluto: %d \n",res);

    return EXIT_SUCCESS;
}
//En el teorico practico deberia mostrarse 10

//Muestra 0 por pantalla, no coincide con el resultado del teorico/practico

