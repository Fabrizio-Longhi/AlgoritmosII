#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    fgets(user_input,MAX_LENGTH,stdin);
    //scanf("%s", user_input);
    strtok(user_input,"\n");
    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

//El problema es que scanf no lee los espacios y automaticamente los saltea
//fgets te va a imprimir hasta que encuentre un espacio,
//strtok toma un deliminador y lo ignora