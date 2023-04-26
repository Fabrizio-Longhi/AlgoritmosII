#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */
#define N 5
#define CELL_MAX (N * N - 1)
void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[N][N])
{
    int cell = 0;

    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

char winner_horizontal(char board[N][N]){
    char winner = '-';
    char cell;
    for (unsigned int i=0; i<N; ++i){
        cell= board[i][0];                      //agarro la primera posicion de la respectiva fila
        for (unsigned int j=0; j<N ; ++j){
            if (cell != board[i][j]){           //comparo el resto de las posiciones, si es distinta, ya no vale
                break;
            }   
            if (j==N-1 && board[i][N-1]!='-'){  //si llegue aca, significa que hice tateti
                winner=cell;
                break;
            }
        }
    }
    return winner;    
}

char winner_vertical(char board[N][N]){
    char winner = '-';
    char cell;
    for (unsigned int j=0; j<N; ++j){
        cell= board[0][j];                      //agarro la primera posicion de la respectiva columna
        for (unsigned int i=0; i<N; ++i){
            if (cell != board[i][j]){           //comparo el resto de las posiciones, si es distinta, ya no vale
                break;      
            }
            if (i==N-1 && board[N-1][j]!='-'){  //si llegue aca, significa que hice tateti
                winner= board[i][j];
            }
        }
    }
    return winner;        
}


char winner_diagonal_izq_a_der(char board[N][N]){
    char winner = '-';
    for (unsigned int i=0; i< N; ++i){
        for (unsigned int j=0; j<N; ++j){
            if (i==j && i!=0){                          //veo diagonal de der a izq
                if (board[i][j] != board[i-1][j-1]){
                    break;
                }
                if (i==N-1 && j==N-1){
                    winner=board[i][j];
                    break;
                }
            }
        }
    }
    return winner;        
}


char winner_diagonal_der_a_izq(char board[N][N]){
    char winner = '-';
    char cell= board[0][N-1];
    unsigned int k=1;
    for (unsigned int i=0; i<N; ++i){
        if (board[i][N-k]!=cell){
            break;
        }
        if(N-k==0){
            winner=board[i][N-k];
            break;
        }
        ++k;
    }

    return winner;
}


char get_winner(char board[N][N])
{
    char winner = '-';  
    if (winner_diagonal_izq_a_der(board)!= '-'){
        winner= winner_diagonal_izq_a_der(board);
    }
    if(winner_diagonal_der_a_izq(board)!= '-'){
        winner=winner_diagonal_der_a_izq(board);
    }
    if (winner_horizontal(board)!= '-'){
        winner= winner_horizontal(board);
    }
    if (winner_vertical(board)!= '-'){
        winner= winner_vertical(board);
    }
    return winner;
}

bool has_free_cell(char board[N][N])
{
    bool free_cell=false;
    for(unsigned int i=0; i<N;++i){
        for (unsigned int j=0; j<N;++j){
            if (board[i][j]== '-'){
                free_cell=true;
            }
        }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");


    char board[N][N];
    for (unsigned int i=0; i<N; ++i){
        for (unsigned j=0; j<N; ++j){
            board[i][j]='-';
        }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / N;
            int colum = cell % N;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}







